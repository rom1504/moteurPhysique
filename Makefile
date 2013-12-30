CCX=g++-4.8
CC=gcc-4.8
CFLAGS=-Wall -std=c++11
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-network
FILES=main Objet Batiment ObjetMobile Unite MoteurPhysique Bouton BoutonImage BoutonTexte Serveur Client Interface EtreVivant Animal Plante Benchmark
OBJECTS=$(FILES:%=temp/%.o)
EXECUTABLE=bin/moteurPhysique
vpath %.cpp source:source/Objet:source/Bouton:source/Reseau:source/Interface:source/EtreVivant:source/Benchmark

all: temp/empty bin/empty $(EXECUTABLE)

-include $(OBJECTS:.o=.d)

$(EXECUTABLE): $(OBJECTS) Makefile
	$(CCX) $(CFLAGS) -o $(EXECUTABLE) $(OBJECTS) $(LDFLAGS)

temp/%.o : %.cpp Makefile
	$(CCX) -c -DSFML_DYNAMIC $(CFLAGS) $< -o $@
	$(CC) -MM $(CFLAGS) $< > temp/$*.d
	@mv -f temp/$*.d temp/$*.d.tmp
	@sed -e 's|.*:|$@:|' < temp/$*.d.tmp > temp/$*.d
	@sed -e 's/.*://' -e 's/\\$$//' < temp/$*.d.tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> temp/$*.d
	@rm -f temp/$*.d.tmp
	
bin/empty:
	mkdir -p bin
	touch bin/empty

temp/empty:
	mkdir -p temp
	touch temp/empty

run: $(EXECUTABLE)
	$(EXECUTABLE)

clean:
	rm -rf bin
	rm -rf temp
