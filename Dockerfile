FROM debian:stretch

MAINTAINER Ahmed Ziabat <aziabatz@alumnos.unex.es>

ENV APT_GET_UPDATE 2016-03-01
ENV code /src
ENV toolchain /toolchain

RUN DEBIAN_FRONTEND=noninteractive apt-get --quiet --yes update \
    && DEBIAN_FRONTEND=noninteractive apt-get --quiet --yes install \
		build-essential \
		bison \
		flex \
		libgmp3-dev \
		libmpfr-dev \
        binutils \
        gcc \
        g++ \
        nasm \
        make \
        wget \
        libmpc-dev \
		texinfo \
        grub \
        grub-pc-bin \
        xorriso \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists

RUN wget http://ftp.gnu.org/gnu/binutils/binutils-2.39.tar.gz \
    && tar xvzf binutils-2.39.tar.gz \
    && cd binutils-2.39 \
    && ./configure --prefix=${toolchain} --target=i686-elf --disable-nls --disable-werror --with-sysroot\
    && make \
    && make install \
    && cd .. \
    && rm -rf binutils-2.39 \
    && rm binutils-2.39.tar.gz

RUN wget http://ftp.gnu.org/gnu/gcc/gcc-12.2.0/gcc-12.2.0.tar.gz \
    && tar xvzf gcc-12.2.0.tar.gz \
    && mkdir build-gcc \
    && cd build-gcc \
    && ../gcc-12.2.0/configure --prefix=${toolchain} --target=i686-elf --disable-nls --enable-languages=c,c++ --without-headers --disable-werror\
    && make all-gcc\
    && make all-target-libgcc\
    && make install-gcc\
    && make install-target-libgcc \
    && cd .. \
    && rm -rf build-gcc \
    && rm -rf gcc-12.2.0 \
    && rm gcc-12.2.0.tar.gz

RUN DEBIAN_FRONTEND=noninteractive apt-get --quiet --yes remove \
    g++ \
    wget \
    libmpc-dev

# COPY . ${code}
ENV PATH="${toolchain}/bin:${PATH}"
WORKDIR ${code}
ENTRYPOINT ["/bin/bash"]

