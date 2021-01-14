.DEFAULT: draft

draft: 
	mkdir -p output
	chmod 755 ./utils/tdr
	BIBINPUTS=.. ./utils/tdr --style=tdr --temp_dir=output b

nodraft: 
	mkdir -p output
	chmod 755 ./utils/tdr
	BIBINPUTS=.. ./utils/tdr --style=tdr --nodraft --temp_dir=output b
