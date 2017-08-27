/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 08:34:55 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/08/27 10:26:03 by gvan-roo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/vm.h"

/*
**	Function for printing out bytes in hexadecimal
*/

void	ft_print_hex(int c)
{
	char *map = "0123456789abcdef";
	
	write(1, map + (c / 16), 1);
	write(1, map + (c % 16), 1);
	write(1, " ", 1);
}


/*
 ** Utility function.
 ** Takes the address of the byte to be converted into hex. This address
 ** needs to be converted into two values, hence key is incremented twice.
 ** The second parameter takes the array into which the values are to be
 ** placed.
 ** Returns the pointer to the next element of the array.
*/

char *add_byte(unsigned char *mem_c, char *key)
{
	char *map = "0123456789abcdef";
	
	*key++ = map[*mem_c / 16];
	*key++ = map[*mem_c % 16];
	return (key);
}

/*
** Main function.
** Takes the address of the buffer that holds the first 4 byte of the FD.
** Takes the total size of the buffer.
** check_key converts the first 4 bytes of the FD into hex, which it then 
** stores in an array.
** It the compares the array to the reference array which is defined in our
** header file.
** If the two arrays match, aka the two magic keys, the function returns 1.
** If the two arrays do not match, the funtion returns 0.
*/

int	check_key(const void *mem, size_t size)
{
	char key[9];
	char *key_c;
	char *ref = "00ea83f3";
	unsigned char *mem_c;
	
	mem_c = (unsigned char *)mem;
	key_c = key;
	while ((size_t)(mem_c - (unsigned char*)mem) < size)
		key_c = add_byte(mem_c++, key_c);
	*key_c = '\0';
	if (ft_strcmp(ref, key) == 0)
		return (1);
	return (0);
}

/*
**	Swops the bytes of a passed argument int
*/

int					swop_bytes(int i, int no_bytes)
{
	if (no_bytes == 4)
	{
		i = (i >> 24 & 0xFF) | (i >> 8 & 0xFF00) |
			(i << 8 & 0xFF0000) | (i << 24 & 0xFF0000);
	}
	return (i);
}


/*
**	Reads the info from file into the champion struct. Calls check magic
**	number func for a valid magic number, and checks the file size of the
**	champion that is does not exceed maximum size. Initialises program
**	carry, pc, registers and next executable cycle.
*/

void				read_champ(int fd, int prog_num, t_champ *champ_ptr)
{
	int				ctr;

	ctr = 2;
	read(fd, (void *)&champ_ptr->head.magic, 4);
	if (!check_key((void *)&champ_ptr->head.magic, 4))
			ft_printf("\nInvalid file magic number\n");
	champ_ptr->head.magic = swop_bytes(champ_ptr->head.magic, 4);
	champ_ptr->player_num = prog_num;
	read(fd, champ_ptr->head.prog_name, PROG_NAME_LENGTH);
	lseek(fd, 136, SEEK_SET);
	read(fd, (void *)&champ_ptr->head.prog_size, 4);
	champ_ptr->head.prog_size = swop_bytes(champ_ptr->head.prog_size, 4);
	if (champ_ptr->head.prog_size > CHAMP_MAX_SIZE)
	{
		ft_printf("\n**** Program size too big for champion %s ****\n\n",
				champ_ptr->head.prog_name);
	}
	read(fd, champ_ptr->head.comment, COMMENT_LENGTH);
	lseek(fd, 2192, SEEK_SET);
	read(fd, champ_ptr->prog, champ_ptr->head.prog_size);
	champ_ptr->alive = 1;
	champ_ptr->carry = 0;
	champ_ptr->pc = 0;
	champ_ptr->reg[1] = champ_ptr->player_num;
	while (ctr < 17)
	{
		champ_ptr->reg[ctr] = 0;
		ctr++;
	}
	champ_ptr->exec_cycle = 1;
}

/*
**	Prints out champ variables. Testing and debug function
*/

void				print_champ(t_champ *champ_ptr)
{
	int				ctr;

	ctr = 0;
	ft_printf("Player num :%i\n", champ_ptr->player_num);
	ft_printf("Program name :%s\n", champ_ptr->head.prog_name);
	ft_printf("Program size :%i\n", champ_ptr->head.prog_size);
	ft_printf("Program comment :%s\n", champ_ptr->head.comment);
	ft_printf("Program alive? :%i\n", champ_ptr->alive);
	ft_printf("Prog carry :%i\n", champ_ptr->carry);
	ft_printf("Prog pc :%i\n", champ_ptr->pc);
	while (++ctr < 17)
		ft_printf("Reg[%i] :%i\n", ctr, champ_ptr->reg[ctr]);
	ft_printf("Prog next cycle :%i\n", champ_ptr->exec_cycle);
	ft_printf("Program binary:\n");
	for (unsigned int i = 0; i < champ_ptr->head.prog_size; i++)
	{	
		ft_print_hex(champ_ptr->prog[i]);
	}
	ft_printf("\n");
}

/*
**	Tries to open files passed as arguments to main. If successfull
**	mallocs space for a new champion, and call read function which
**	reads the file info into the champion struct.
*/

void				open_files(int ac, char **av, t_champ *champ_ptr)
{
	int				ctr;
	int				fd;

	ctr = 1;
	while (ctr < ac)
	{
		fd = open(av[ctr], O_RDONLY);
		if (fd < 0)
		{
			ft_printf("Unable to open file %s - exiting\n", av[ctr]);
			exit (0);
		}
		if (champ_ptr == NULL)
			champ_ptr = ft_memalloc(sizeof(t_champ));
		else
		{
			champ_ptr->next = ft_memalloc(sizeof(t_champ));
			champ_ptr = champ_ptr->next;
		}
		champ_ptr->next = NULL;
		read_champ(fd, ctr, champ_ptr);
		print_champ(champ_ptr);
		ft_printf("\n");
		close(fd);
		ctr++;
	}
}

void				init_vm(t_vm vm, t_champ *champ_head)
{
	t_champ			*champ_ptr;

	champ_ptr = champ_head;
}


int					main(int argc, char **argv)
{
	t_champ			*champ_head;
//	t_vm			vm;
	
	if (argc < 2 || argc > 5)
	{
		ft_printf("Usage with max %i champs: ./corewar <champ1.cor> <...>\n",
				MAX_PLAYERS);
		return (0);
	}
	champ_head = NULL;	
	open_files(argc, argv, champ_head);
//	init_vm(vm, champ_head);
//	free_champs;
	return (0);
}
