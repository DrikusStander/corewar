/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 08:35:37 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/09/01 11:32:44 by hstander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __VM_H
# define __VM_H

# include <fcntl.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include "../libft/libft.h"


#define IND_SIZE				2
#define REG_SIZE				4
#define DIR_SIZE				REG_SIZE


# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3


#define MAX_ARGS_NUMBER			4
#define MAX_PLAYERS				4
#define MEM_SIZE				(4*1024)
#define IDX_MOD					(MEM_SIZE / 8)
#define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

#define COMMENT_CHAR			'#'
#define LABEL_CHAR				':'
#define DIRECT_CHAR				'%'
#define SEPARATOR_CHAR			','

#define LABEL_CHARS				"abcdefghijklmnopqrstuvwxyz_0123456789"

#define NAME_CMD_STRING			".name"
#define COMMENT_CMD_STRING		".comment"

#define REG_NUMBER				16

#define CYCLE_TO_DIE			20//1536
#define CYCLE_DELTA				50
#define NBR_LIVE				21
#define MAX_CHECKS				10

typedef char	t_arg_type;

#define T_REG					1
#define T_DIR					2
#define T_IND					4
#define T_LAB					8

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef struct          s_op
{
	char                *name;
	int                 no_args;
	char                type[MAX_ARGS_NUMBER];
	char                id;
	int                 no_cycles;
	char                *desc;
	int                 has_acb;
	int                 is_index;
}                       t_op;

extern  t_op            g_op_tab[];

typedef struct header_s	header_t;
typedef struct s_champ	t_champ;
typedef struct s_vm		t_vm;

struct					header_s
{
	unsigned int		magic;
	char				prog_name[PROG_NAME_LENGTH + 1];
	unsigned int		prog_size;
	char				comment[COMMENT_LENGTH + 1];
};

struct					s_champ
{
	int					player_num;
	header_t			head;
	unsigned char		prog[CHAMP_MAX_SIZE];
	int					alive;
	int					called_alive;
	int					carry;
	int					pc;
	int					reg[17];
	int					exec_cycle;
	struct s_champ		*next;
};

struct					s_vm
{
	unsigned char		mem[MEM_SIZE];
	unsigned int		cur_cycle;
	unsigned int		cycle_to_die;
	unsigned int		cycle_delta;
	unsigned int		live_calls;
	unsigned int		checks;
	unsigned int		last_live;
	void				(*func[17])(t_vm *, t_champ *);
};

/*
 **	check_key_swop_bytes.c
 */

char					*add_byte(unsigned char *mem_c, char *key);
int						check_key(const void *mem, size_t size);
int						swop_bytes(int i, int no_bytes);

/*
 **	open_files.c
 */

void					read_champ(int fd, int prog_num, t_champ *champ_ptr);
void					open_files(int ac, char **av, t_champ *champ_ptr);

/*
 **	print_mem.c
 */

void					ft_print_hex(int c);
unsigned char			*print_line(unsigned char *mem, size_t size);
void					print_memory(const void *addr, size_t size);

/*
 **	init_vm.c
 */

void					alloc_champ_mem(t_vm *vm, t_champ *champ_ptr, int offset);
void					init_vm(t_vm *vm, t_champ *champ_head, int argc);

/*
 **	print_champ_mem.c
 */

void					print_vm(t_vm vm);
void					print_champ(t_champ *champ_ptr);

/*
 **	run_machine_run.c
 */

int						check_who_alive(t_champ *champ_head);
void					new_cycle_to_die(t_champ *champ_head, t_vm *vm);
void					call_live(t_champ *champ_head, t_champ *champ_ptr, t_vm *vm);
void					exec_champ(t_champ *champ_head,
							t_champ *champ_ptr, t_vm *vm);
void					run_machine_run(t_champ *champ_head, t_vm *vm);

/*
 **	opcodes .c
 */

void					ft_ld(t_vm *vm, t_champ *champ);
void					ft_st(t_vm *vm, t_champ *champ);
void					ft_add(t_vm *vm, t_champ *champ);
void					ft_sub(t_vm *vm, t_champ *champ);
void					ft_and(t_vm *vm, t_champ *champ);
void					ft_or(t_vm *vm, t_champ *champ);
void					ft_xor(t_vm *vm, t_champ *champ);
void					ft_zjmp(t_vm *vm, t_champ *champ);
void					ft_ldi(t_vm *vm, t_champ *champ);
void					ft_sti(t_vm *vm, t_champ *champ);
void					ft_fork(t_vm *vm, t_champ *champ);
void					ft_lld(t_vm *vm, t_champ *champ);
void					ft_lldi(t_vm *vm, t_champ *champ);
void					ft_lfork(t_vm *vm, t_champ *champ);
void					ft_aff(t_vm *vm, t_champ *champ);
void					ft_decode(unsigned int i, unsigned char *buf);
int						to_signed_int(unsigned int value, int bitLength);
int						mem_check(int pc);
void					init_champ(t_champ *champ, t_champ *new_champ);

#endif
