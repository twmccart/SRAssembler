bootstrap: docker
From: fedora:27

%help
    This container provides portable & reproducible components for SRAssembler:
    Selective Recursive local Assembler from the Brendel Group.
    Please see https://github.com/BrendelGroup/SRAssembler for complete documentation.
    To run single-threaded, use `singularity run SRAssembler.img` with appropriate arguments.
    To run multi-threaded, you must have openmpi installed.
    Use `mpirun -np $processornumber singularity run --app mpi SRAssembler.img` with appropriate arguments.

%post
    dnf -y update
    dnf -y install @development-tools
    dnf -y install gcc-c++
    dnf -y install bc git tcsh tzdata unzip zip wget which
    dnf -y install nano

    echo 'Installing Abyss assembler '
    #### Prerequisites
    dnf -y install boost-devel
    dnf -y install autoconf automake
    dnf -y install sparsehash-devel
    dnf -y install openmpi openmpi-devel
    export PATH=$PATH:/usr/lib64/openmpi/bin
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/lib64/openmpi/lib
    #### Install
    cd /opt
    git clone https://github.com/bcgsc/abyss.git
    cd abyss
    ./autogen.sh
    ./configure
    make
    
    echo 'Installing SOAPdenovo2 assembler '
    #### Prerequisites
    #### Install
    cd /opt
    git clone https://github.com/aquaskyline/SOAPdenovo2.git
    cd SOAPdenovo2
    make
    
    echo 'Installing VMATCH aligner from http://vmatch.de '
    #### Prerequisites
    #### Install
    cd /opt
    wget http://vmatch.de/distributions/vmatch-2.3.0-Linux_x86_64-64bit.tar.gz
    tar -xzf vmatch-2.3.0-Linux_x86_64-64bit.tar.gz
    rm vmatch-2.3.0-Linux_x86_64-64bit.tar.gz
    ln -s vmatch-2.3.0-Linux_x86_64-64bit VMATCH
    chown -R root:users VMATCH
    chmod a-s VMATCH
    chmod a+x VMATCH
    chmod a+r VMATCH
    cd VMATCH
    chmod a+r chain2dim cleanpp.sh matchcluster mkdna6idx mkvtree repfind.pl upgradeprj.pl vendian vmatch vmatchselect Vmatchtrans.pl vmigrate.sh vseqinfo vseqselect vstree2tex vsubseqselect
    chmod a+x chain2dim cleanpp.sh matchcluster mkdna6idx mkvtree repfind.pl upgradeprj.pl vendian vmatch vmatchselect Vmatchtrans.pl vmigrate.sh vseqinfo vseqselect vstree2tex vsubseqselect
    chmod a+r *pdf README.distrib SELECT TRANS
    chmod a+x SELECT TRANS
    chmod a+r SELECT/*
    chmod a+r TRANS/*

    echo 'Installing BLAST+ from NCBI '
    #### Prerequisites
    #### Install
    cd /opt
    wget ftp://ftp.ncbi.nlm.nih.gov/blast/executables/blast+/LATEST/ncbi-blast-2.7.1+-x64-linux.tar.gz
    tar -xzf ncbi-blast-2.7.1+-x64-linux.tar.gz
    rm ncbi-blast-2.7.1+-x64-linux.tar.gz
    ln -s ncbi-blast-2.7.1+ BLAST

    echo 'Installing GeneSeqer spliced aligner '
    #### Prerequisites
    #### Install
    cd /opt
    git clone https://github.com/BrendelGroup/GeneSeqer.git
    cd GeneSeqer/src
    make linux
    
    echo 'Installing GenomeThreader spliced aligner '
    #### Prerequisites
    #### Install
    cd /opt
    wget http://genomethreader.org/distributions/gth-1.7.0-Linux_x86_64-64bit.tar.gz
    tar -xzf gth-1.7.0-Linux_x86_64-64bit.tar.gz
    rm gth-1.7.0-Linux_x86_64-64bit.tar.gz
    ln -s gth-1.7.0-Linux_x86_64-64bit GENOMETHREADER

    echo 'Installing SNAP gene finder '
    #### Prerequisites
    #### Install
    cd /opt
    git clone https://github.com/KorfLab/SNAP.git
    cd SNAP
    make
        
    echo 'Installing SRAssembler from https://github.com/BrendelGroup/SRAssembler.git '
    #### Prerequisites
    #### Install
    cd /opt
    git clone https://github.com/BrendelGroup/SRAssembler.git
    cd SRAssembler/src
    make
    make clean
    make mpi
    make clean

%environment
    export PATH=$PATH:/opt/VMATCH
    export PATH=$PATH:/opt/SOAPdenovo2
    export PATH=$PATH:/opt/GeneSeqer/bin
    export PATH=$PATH:/opt/BLAST/bin
    export PATH=$PATH:/opt/GENOMETHREADER/bin
    export PATH=$PATH:/opt/SNAP
    export PATH=$PATH:/opt/abyss/bin
    export PATH=$PATH:/opt/abyss/ABYSS
    export PATH=$PATH:/usr/lib64/openmpi/bin
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/lib64/openmpi/lib
    export BSSMDIR="/opt/GENOMETHREADER/bin/bssm"
    export GTHDATADIR="/opt/GENOMETHREADER/bin/gthdata"
    export ZOE="/opt/SNAP"
    export PATH=$PATH:/opt/SRAssembler/bin

%runscript
    exec SRAssembler "$@"

%apprun mpi
    exec SRAssembler_MPI "$@"

%test
    #cd /opt/SRAssembler/demo
    #./xtest


%labels
    Maintainer vpbrendel
    Version v1.0