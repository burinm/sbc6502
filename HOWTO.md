# Building
The binaries for sbc require a working **cc65 compiler**, **srec_cat** (from srecord-1.64), and **x65dsasm**. See **target.mk** to change the default location of /opt for these tools

## 0. Grab source
```
git clone https://github.com/burinm/sbc6502.git
git clone https://github.com/burinm/drivers.git
```

## 1. Install cc65 compiler suite
```
git clone https://github.com/cc65/cc65.git
cd cc65
make

sudo mkdir /opt/cc65
sudo make install PREFIX=/opt/cc65
cd -
```


Modify environment (see .bashrc below)


## 2. Install srecord

http://srecord.sourceforge.net/

```
wget http://srecord.sourceforge.net/srecord-1.64.tar.gz
gunzip srecord-1.64.tar.gz
tar xvf srecord-1.64.tar
cd srecord-1.64/
```


(possible dependencies)

```
sudo apt-get install libboost-dev
sudo apt-get install libtool-bin
```

```
./configure --prefix=/opt/srecord --without-gcrypt
make
sudo make install
cd -
```


Modify environment (see .bashrc below)

## 3. Install x65dsasm
```
git clone https://github.com/Sakrac/x65dsasm
cd x65dsasm
```


Add this to struse.h:

```
    #define nullptr NULL
```


Add a Makefile:

```
x65dsasm: x65dsasm.cpp
	g++ $^ -o $@

clean:
	rm -rf x65dsasm
```


Then make

```
make
sudo mkdir -p /opt/6502bin
sudo cp x65dsasm /opt/6502bin
cd -
```


## 4. Finally build all the binaries for sbc!

```
cd sbc6502
make
```



There should now be this:

```
find bin/

    bin/
    bin/blink_stack.map
    bin/blink_fader.map
    bin/blink_knightrider.hex
    bin/bootloader.dis
    bin/blink_stack.dis
    bin/blink_fader.dis
    bin/blink_knightrider.bin
    bin/bootloader.bin
    bin/blink_knightrider.map
    bin/bootloader.hex
    bin/blink_stack.hex
    bin/blink_fader.hex
    bin/blink_stack.bin
    bin/.hold
    bin/blink_fader.bin
    bin/blink_knightrider.dis
    bin/bootloader.map
```

# .bashrc
-------
```
#cc65
export CA65_INC=/opt/cc65/share/cc65/asminc
export CC65_INC=/opt/cc65/share/cc65/include
export LD65_CFG=/opt/cc65/share/cc65/cfg
export LD65_LIB=/opt/cc65/share/cc65/lib
export LD65_OBJ=/opt/cc65/share/cc65/lib
export CC65_HOME=/opt/cc65

#srecord
MANPATH=${MANPATH}:/opt/srecord/share/man
```

# .vimrc
------
```
augroup filetypedetect
 ...
  au BufNewFile,BufRead *.dis set filetype=65c02 syntax=65c02
 ...
augroup END
```
