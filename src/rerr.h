
#define RENDR_OK 0
#define RENDR_FAILURE 1

#define RNDRR_ASRT(condition, msg)       \
    do {                                  \
        if (condition) {                  \
            fprintf(stderr, "%s\n", msg); \
            return RENDR_FAILURE;         \
        }                                 \
    } while (0)
