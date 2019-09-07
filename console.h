#define BUFFER_SIZE	4000
#define MAX_LINES	25
#define MAX_CHARS	80

#define BLACK		0x0
#define BLUE		0x1
#define GREEN		0x2
#define CYAN		0x3
#define RED			0x4
#define MAGENTTA	0x5
#define BROWN		0x6
#define LIGHT_GRAY	0x7
#define GRAY		0x8
#define LIGHT_BLUE	0x9
#define LIGHT_GREEN	0xA
#define LIGHT_CYAN	0xB
#define LIGHT_RED	0xC
#define LIGHT_MAGENTA	0xD
#define LIGHT_YELLOW	0xE
#define WHITE		0xF

void kclear();
int kprintf(const  char *str);
