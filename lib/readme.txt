To generate a library from supervision.lib with a different CPU architeture,
modify the source compilation Makefile:

cd cc65/libsrc

make "CA65FLAGS=--cpu 6502" supervision
cp ../lib/supervision.lib xxx

    
make "CA65FLAGS=--cpu 65c02" supervision
cp ../lib/supervision.lib xxx

