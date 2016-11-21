
#CUPL := /cygdrive/c/Wincupl/Shared/cupl.exe
CUPL := ~/.wine/drive_c/Wincupl/Shared/cupl.exe
ATMELDL := C:\\Wincupl\\Shared\\Atmel.dl

PLDS = *.pld
JEDS = $(PLDS:%.pld=%.jed)
CLEANOBJS = *.lst *.jed *.abs *.sim	*.doc *.abs *.pdf *.pla *.wo *.so

DATE := $(shell date +'%s')
TARGETOUT := sbc32k32k.$(DATE).jed
TARGET := out.hex
INPUT := blink

all: $(TARGETOUT)
$(TARGETOUT): sbc32k32k.jed
	cp $^ $@
	rm $^

%.jed : %.pld 
	$(CUPL) -jlm1a -u $(ATMELDL) $< 

sim : $(PLDS)
	$(CUPL) -jlm1as -u $(ATMELDL) $<

clean:
	rm -f $(CLEANOBJS) || true

upload:
	cp $(JEDS) ~/Dropbox/temp
z:
	scp $(JEDS) burinj@eces.colorado.edu:~/
