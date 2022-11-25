ARG OS_TYPE
ARG OS_TAG

FROM ${OS_TYPE}:${OS_TAG}

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update    && \
    apt-get install -y   \
      tzdata             \
      libfreetype-dev    \
      libglu1-mesa-dev   \
      freeglut3-dev      \
      mesa-common-dev    \
      libglew-dev        \
      python3-dev        \
      python3-matplotlib \
      locales-all        \
      make               \
      autoconf           \
      automake           \
      cmake              \
      ninja-build        \
      dos2unix           \
      rsync              \
      tar                \
      git                \
      catch2             \
      ccache             \
      build-essential    \
      gdb                \
      gcc-12             \
      g++-12          && \
    apt-get clean -y


# Install Clang
ARG CLANG_VER=""

COPY "llvm.sh" /tmp/llvm.sh
WORKDIR /tmp

RUN apt-get update                                       && \
    apt-get install -y                                      \
      --no-install-recommends software-properties-common    \
      lsb-release                                           \
      wget

RUN if [ -n "${CLANG_VER}" ] ; then bash llvm.sh ${CLANG_VER} ; fi

RUN apt-get clean -y

ARG UID=1000
RUN useradd -m -u ${UID} -s /bin/bash builder
USER builder
