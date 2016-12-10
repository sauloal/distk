curl ftp://ftp.solgenomics.net/genomes/Solanum_lycopersicum/assembly/build_2.50/SL2.50ch00.fa | grep -v '>' | tr -d '\n' > test4.fasta
curl ftp://ftp.solgenomics.net/genomes/Solanum_lycopersicum/assembly/build_2.50/SL2.50ch{00,01,02,03,04,05,06,07,08,09,10,11,12}.fa | grep -v '>' | tr -d '\n' > test5.fasta
