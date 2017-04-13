#define FULL 0
#define NOFULL 42
#define TUBESTART sizeof(strut conduct)

struct conduct{
  char full;
  size_t capacite;
  size_t t_atomique;
  unsigned int p_read;
  unsigned int p_write;
  char* tube;
};

struct conduct *conduct_create(const char *name, size_t a, size_t c);
struct conduct *conduct_open(const char *name);
ssize_t conduct_read(struct conduct *c, void *buf, size_t count);
ssize_t conduct_write(struct conduct *c, const void *buf, size_t count);
int conduct_write_eof(struct conduct *c);
void conduct_close(struct conduct *conduct);
void conduct_destroy(struct conduct *conduct);
