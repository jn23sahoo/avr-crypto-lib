# Makefile for the micro-crypt project
# author: Daniel Otte

BLOCK_CIPHERS  := 
STREAM_CIPHERS := 
HASHES         :=
MACS           :=
PRNGS          := 

# we use the gnu make standard library
include gmsl
include avr-makefile.inc
include mkfiles/*.mk

ALGORITHMS = $(BLOCK_CIPHERS) $(STREAM_CIPHERS) $(HASHES) $(PRNGS) $(MACS)
ALGORITHMS_OBJ = $(patsubst %,%_OBJ, $(ALGORITHMS))
define OBJinBINDIR_TEMPLATE
$(1) = $(2)
endef
$(foreach a, $(ALGORITHMS_OBJ), $(eval $(call OBJinBINDIR_TEMPLATE, $(a), $(patsubst %.o,$(BIN_DIR)%.o,$($(a))))))
ALGORITHMS_TEST_BIN = $(patsubst %,%_TEST_BIN, $(ALGORITHMS))
$(foreach a, $(ALGORITHMS_TEST_BIN), $(eval $(call OBJinBINDIR_TEMPLATE, $(a), $(patsubst %.o,$(TESTBIN_DIR)%.o,$($(a))))))


ALGORITHMS_TEST_BIN_IMM =  $(foreach a, $(ALGORITHMS_TEST_BIN), $($(a)))
ALGORITHMS_NESSIE_TEST = $(patsubst %,%_NESSIE_TEST, $(ALGORITHMS))
ALGORITHMS_PERFORMANCE_TEST = $(patsubst %,%_PERORMANCE_TEST, $(ALGORITHMS))

ALGORITHMS_LC = $(call lc,$(ALGORITHMS))

ALGORITHMS_TEST_TARGET_ELF = $(patsubst %, $(TESTBIN_DIR)main-%-test.elf, $(ALGORITHMS_LC))
ALGORITHMS_TEST_TARGET_HEX = $(patsubst %, $(TESTBIN_DIR)main-%-test.hex, $(ALGORITHMS_LC))


#-------------------------------------------------------------------------------

all: $(foreach algo, $(ALGORITHMS), $(algo)_OBJ)

#-------------------------------------------------------------------------------

define MAIN_OBJ_TEMPLATE
$(2): $(3) $(4)
	@echo "[ld]: $$@"
#	echo $$^
	@$(CC) $(CFLAGS) $(LDFLAGS)$(patsubst %.elf,%.map,$(2)) -o \
	$(2) \
	$(3) $(4) \
	$(LIBS)
endef

$(foreach algo, $(ALGORITHMS), $(eval $(call MAIN_OBJ_TEMPLATE, \
   $(algo), \
   $(TESTBIN_DIR)main-$(call lc,$(algo))-test.elf, \
   $(patsubst %.o,%.o,$($(algo)_TEST_BIN)), \
   $(patsubst %.o,%.o,$($(algo)_OBJ))  )))




#-------------------------------------------------------------------------------
.PHONY: help
help: info

info:
	@echo "infos on micro-crypt:"
	@echo "  block ciphers:"
	@echo "    $(BLOCK_CIPHERS)"
	@echo "  stream ciphers:"
	@echo "    $(STREAM_CIPHERS)"
	@echo "  hash functions:"
	@echo "    $(HASHES)"
	@echo "  MAC functions:"
	@echo "    $(MACS)"
	@echo "  PRNG functions:"
	@echo "    $(PRNGS)"
#	@echo "  ALGORITHMS_TEST_BIN"
#	@echo "    $(ALGORITHMS_TEST_BIN)"
#	@echo "  ALGORITHMS_TEST_TARGET_ELF:"
#	@echo "    $(ALGORITHMS_TEST_TARGET_ELF)"

#-------------------------------------------------------------------------------
	

$(BIN_DIR)%.o: %.c
	@echo "[gcc]:  $@"
	@$(CC) $(CFLAGS)  -c -o $@ $<

$(BIN_DIR)%.o: %.S
	@echo "[as] :  $@"
	@$(CC) $(ASFLAGS) -c -o $@ $<

$(TESTBIN_DIR)%.o: $(TESTSRC_DIR)%.c
	@echo "[gcc]:  $@"
	@$(CC) $(CFLAGS)  -c -o $@ $<

$(TESTBIN_DIR)%.o: $(TESTSRC_DIR)%.S
	@echo "[as] :  $@"
	@$(CC) $(ASFLAGS) -c -o $@ $<


%.o: %.c
	@echo "[gcc]:  $@"
	@$(CC) $(CFLAGS)  -c -o $@ $<

%.o: %.S
	@echo "[as] :  $@"
	@$(CC) $(ASFLAGS) -c -o $@ $<

#-------------------------------------------------------------------------------
	
define OBJ_TEMPLATE
$(1)_OBJ: $(2)
#	@echo " ALGO: $(1)"
#	@echo " REQ:  $(2)"
endef

$(foreach algo, $(ALGORITHMS), $(eval $(call OBJ_TEMPLATE, $(algo), $($(algo)_OBJ))))

#-------------------------------------------------------------------------------

$(BLOCK_CIPHERS_OBJ): $(patsubst %,%_OBJ, $(BLOCK_CIPHERS)) 
$(STREAM_CIPHERS_OBJ): $(patsubst %,%_OBJ, $(STREAM_CIPHERS))
$(HASHES_OBJ): $(patsubst %,%_OBJ, $(HASHES))
$(PRNGS_OBJ): $(patsubst %,%_OBJ, $(PRNGS))
$(MACS_OBJ): $(patsubst %,%_OBJ, $(MACS))

$(ALGORITHMS_TEST_BIN): $(ALGORITHMS_TEST_BIN_IMM)

#-------------------------------------------------------------------------------

define SIZE_TEMPLATE
$(1)_size.txt: $(2)
	@echo "[size]: $(1)_size.txt"
	@$(SIZE) $(2) > $(1)_size.txt
endef

$(foreach algo, $(ALGORITHMS), $(eval $(call SIZE_TEMPLATE, $(STAT_DIR)$(call lc,$(algo)), $($(algo)_OBJ))))

#-------------------------------------------------------------------------------

define FLASH_TEMPLATE
$(1)_FLASH: $(2)
	@echo "[flash]: $(2)"
	@$(FLASHCMD)$(call first,$(2))
endef

$(foreach algo, $(ALGORITHMS),$(eval $(call FLASH_TEMPLATE, $(algo), $(TESTBIN_DIR)main-$(call lc,$(algo))-test.hex) ))  

#-------------------------------------------------------------------------------

define TESTRUN_TEMPLATE
$(1)_TESTRUN: $(1)_FLASH
	@echo "[test]: $(1)"
	$(RUBY) get_test.rb  $(TESTPORT) $(TESTPORTBAUDR) 8 1 nessie $(TESTLOG_DIR)$(TESTPREFIX) $(2)
endef

$(foreach algo, $(ALGORITHMS),$(eval $(call TESTRUN_TEMPLATE, $(algo), $(call lc,$(algo)) )))

ALL_TESTRUN: $(foreach algo, $(ALGORITHMS), $(algo)_TESTRUN)

#-------------------------------------------------------------------------------

define LISTING_TEMPLATE
$(1)_LIST: $(2)
endef

$(foreach algo, $(ALGORITHMS),$(eval $(call LISTING_TEMPLATE,$(call uc, $(algo)), $(patsubst %.o,%.lst,$(algo)_OBJ) )))

listings: $(patsubst %,%_LIST,$(ALGORITHMS))


$(LIST_DIR)%.lst: $(TESTBIN_DIR)%.elf
	$(OBJDUMP) -h -S $< > $@

$(LIST_DIR)%.lst: $(BIN_DIR)%.o
	$(OBJDUMP) -h -S $< > $@

$(LIST_DIR)%.lst: $(TESTBIN_DIR)%.o
	$(OBJDUMP) -h -S $< > $@

#-------------------------------------------------------------------------------

.PHONY: cores
cores: $(ALGORITHMS_OBJ)

.PHONY: blockciphers
blockciphers: $(patsubst %, %_OBJ, $(BLOCK_CIPHERS))

.PHONY: streamciphers
streamciphers: $(patsubst %, %_OBJ, $(STREAM_CIPHERS))

.PHONY:  hashes
hashes: $(patsubst %, %_OBJ, $(HASHES))

.PHONY:  macs
macs: $(patsubst %, %_OBJ, $(MACS))

.PHONY:  prngs
prngs: $(patsubst %, %_OBJ, $(PRNGS))

tests: $(ALGORITHMS_TEST_BIN) \
       $(ALGORITHMS_TEST_TARGET_ELF) \
       $(ALGORITHMS_TEST_TARGET_HEX)

.PHONY:  stats
stats: $(SIZESTAT_FILE)
	@cat $(STAT_DIR)$(SIZESTAT_FILE)	
	
$(SIZESTAT_FILE): $(patsubst %, $(STAT_DIR)%_size.txt, $(ALGORITHMS_LC))
	$(RUBY) sumsize.rb $^ > $(STAT_DIR)$(SIZESTAT_FILE)
	
#-------------------------------------------------------------------------------	


.PHONY: clean
clean:
	rm -rf $(BIN_DIR)*.o *.o $(TESTBIN_DIR)*.elf $(TESTBIN_DIR)* *.elf *.eps *.png *.pdf *.bak
	rm -rf *.lst *.map $(EXTRA_CLEAN_FILES) $(STAT_DIR)$(SIZESTAT_FILE) $(STAT_DIR)*_size.txt
xclean: clean
	rm -rf $(DEP_DIR)*.d

docu:
	doxygen



# Rules for building the .text rom images

%.hex: %.elf
	@echo "[objcopy]: $@"
	@$(OBJCOPY) -j .text -j .data -O ihex $< $@

%.srec: %.elf
	@echo "[objcopy]: $@"
	@$(OBJCOPY) -j .text -j .data -O srec $< $@

%.bin: %.elf
	@echo "[objcopy]: $@"
	@$(OBJCOPY) -j .text -j .data -O binary $< $@

# Rules for building the .eeprom rom images


%_eeprom.hex: %.elf
	@echo "[objcopy]: $@"
	@$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O ihex $< $@

%_eeprom.srec: %.elf
	@echo "[objcopy]: $@"
	@$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O srec $< $@

%_eeprom.bin: %.elf
	@echo "[objcopy]: $@"
	@$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O binary $< $@
	
	
# Every thing below here is used by avr-libc's build system and can be ignored
# by the casual user.

FIG2DEV		 = fig2dev
EXTRA_CLEAN_FILES       = *.hex *.bin *.srec


%.eps: %.fig
	$(FIG2DEV) -L eps $< $@

%.pdf: %.fig
	$(FIG2DEV) -L pdf $< $@

%.png: %.fig
	$(FIG2DEV) -L png $< $@


DEPS := $(wildcard $(DEP_DIR)*.d)

ifneq ($(DEPS),)
include $(DEPS)
endif

