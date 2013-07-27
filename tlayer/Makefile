####
#### Sample Makefile for building apps with the RIOT OS
####
#### The Sample Filesystem Layout is:
#### /this makefile
#### ../../RIOT 
#### ../../boards   for board definitions (if you have one or more)
#### 

# name of your project
export PROJECT =tlayer

# for easy switching of boards
export BOARD = agilefox

# this has to be the absolute path of the RIOT-base dir
export RIOTBASE =$(CURDIR)/../../RIOT
export RIOTCPU =$(CURDIR)/../../RIOT/cpu
export RIOTBOARD =$(CURDIR)/../../boards

ifeq ($(BOARD),agilefox)
	include Makefile.$(BOARD)
endif

## Modules to include. 

USEMODULE += auto_init
USEMODULE += vtimer
USEMODULE += ps
USEMODULE += config
USEMODULE += at86rf231
USEMODULE += net_help
USEMODULE += sixlowpan
USEMODULE += destiny
USEMODULE += uart0
USEMODULE += posix
#USEMODULE += ltc4150

export INCLUDES=-I$(RIOTBOARD)/$(BOARD)/include -I$(RIOTBASE)/core/include -I$(RIOTCPU)/$(CPU)/include -I$(RIOTBASE)/sys/lib -I$(RIOTBASE)/sys/include/ -I$(RIOTBASE)/drivers/include/ -I$(RIOTBASE)/drivers/at86rf231/include/ -I$(RIOTBASE)/sys/net/ -I$(RIOTBASE)/sys/net/sixlowpan/

include $(RIOTBASE)/Makefile.include
