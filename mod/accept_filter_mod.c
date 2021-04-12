#include <sys/cdefs.h>
__FBSDID("$FreeBSD$");

#define ACCEPT_FILTER_MOD

#include <sys/param.h>
#include <sys/kernel.h>
#include <sys/module.h>
#include <sys/sysctl.h>
#include <sys/signalvar.h>
#include <sys/socketvar.h>

static int sohasdata(struct socket *so, void *arg, int waitflag);
static void * create_stub(struct socket *so, char *arg);

ACCEPT_FILTER_DEFINE(accf_exploit, "exploit", sohasdata, create_stub, NULL, 1);

static int
sohasdata(struct socket *so, void *arg, int waitflag)
{

	if (!soreadable(so))
		return (SU_OK);

	return (SU_ISCONNECTED);
}

static void *
create_stub(struct socket *so, char *arg) 
{
    return (void *)1;
}