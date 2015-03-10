CC=gcc #clang -ferror-limit=2
SSM_CFLAGS=$(CFLAGS) -std=gnu99 -O3 -DGSL_RANGE_CHECK_OFF -I $(HOME)/.ssm/include
SSM_LDFLAGS=$(LDFLAGS) -lssm -lssmtpl -lssm -lssmtpl -lm -lgsl -lgslcblas -ljansson -lzmq -lpthread
LIB=libssmtpl.a
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

EXEC=simul simplex smc mif pmcmc kalman ksimplex kmcmc worker

all: $(LIB)

install: $(EXEC)
	mv $(EXEC) ../../

$(LIB): $(OBJ)
	ar -rcs $@ $(OBJ)

%.o: %.c
	$(CC) $(SSM_CFLAGS) -o $@ -c $<

simul: libssmtpl.a
	$(CC) $(SSM_CFLAGS) -L. -L$(HOME)/.ssm/lib -o $@ -lssmsimul $(SSM_LDFLAGS)

simplex: libssmtpl.a
	$(CC) $(SSM_CFLAGS) -L. -L$(HOME)/.ssm/lib -o $@ -lssmsimplex $(SSM_LDFLAGS)

smc: libssmtpl.a
	$(CC) $(SSM_CFLAGS) -L. -L$(HOME)/.ssm/lib -o $@ -lssmsmc $(SSM_LDFLAGS) 

mif: libssmtpl.a
	$(CC) $(SSM_CFLAGS) -L. -L$(HOME)/.ssm/lib -o $@ -lssmmif $(SSM_LDFLAGS)  

pmcmc: libssmtpl.a
	$(CC) $(SSM_CFLAGS) -L. -L$(HOME)/.ssm/lib -o $@ -lssmpmcmc $(SSM_LDFLAGS)  

kalman: libssmtpl.a
	$(CC) $(SSM_CFLAGS) -L. -L$(HOME)/.ssm/lib -o $@ -lssmkalman $(SSM_LDFLAGS) 

ksimplex: libssmtpl.a
	$(CC) $(SSM_CFLAGS) -L. -L$(HOME)/.ssm/lib -o $@ -lssmksimplex $(SSM_LDFLAGS)

kmcmc: libssmtpl.a
	$(CC) $(SSM_CFLAGS) -L. -L$(HOME)/.ssm/lib -o $@ -lssmkmcmc $(SSM_LDFLAGS)

worker: libssmtpl.a
	$(CC) $(SSM_CFLAGS) -L. -L$(HOME)/.ssm/lib -o $@ -lssmworker $(SSM_LDFLAGS) 

.PHONY: clean

clean:
	rm *.o $(LIB)

uninstall: clean
	rm ../../{simul,simplex,smc,mif,pmcmc,kalman,ksimplex,kmcmc,worker}
