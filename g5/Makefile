STUDENTS=Hoei_Enevoldsen_Beest
ASSIGNMENT=5
VERSION=1

TAR_GZ=$(STUDENTS)-G$(ASSIGNMENT)-v$(VERSION).tar.gz

all: $(TAR_GZ)

$(TAR_GZ):
	make -C kudos/kudos/ clean
	make -C kudos/userland/ clean
	tar cvzf $(TAR_GZ) \
		kudos/kudos/ \
		kudos/userland/ \
		kudos/yams.conf

clean:
	rm -rf $(TAR_GZ)

.PHONY: all clean
