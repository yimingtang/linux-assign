typedef	int boolean;
#define		true	1
#define		false	0

/*
 *Pointer to function returning boolean
 */
typedef boolean (*PFUNC)();

enum comparison_type
{
	COMP_GT,
	COMP_LT,
	COMP_EQ
};

enum predicate_type
{
	NO_TYPE,
	PRIMARY_TYPE,
	UNI_OP,
	BI_OP,
	LEFT_PAREN,
	RIGHT_PAREN
};


struct	predicate
{
	//only use in DEBUG mode
	char *p_name;
	PFUNC pred_func;
	struct predicate *pred_next;
	struct predicate *pred_left;
	struct predicate *pred_right;

	union
	{
		char *str;
		uid_t uid;
		gid_t gid;
		time_t time;
		unsigned long perm;
		unsigned long type;
		FILE *stream;
}
