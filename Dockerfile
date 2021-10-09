FROM debian:bullseye

ENV TZ=Europe/Warsaw
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt update && apt -y install build-essential cmake git curl unzip tar zip make pkg-config

RUN git clone https://github.com/Microsoft/vcpkg.git /vcpkg

WORKDIR /vcpkg

RUN ./bootstrap-vcpkg.sh && ./vcpkg integrate install && ./vcpkg integrate bash && echo 'export PATH=$PATH:/vcpkg' >>~/.bashrc

WORKDIR /app
COPY . .

WORKDIR /app/build
RUN cmake .. -DCMAKE_TOOLCHAIN_FILE=/vcpkg/scripts/buildsystems/vcpkg.cmake \
    || (sed -i '51 s/.*/#&/'  ./vcpkg_installed/x64-linux/share/sleepy-discord/sleepy-discord-config.cmake \
    && cmake .. -DCMAKE_TOOLCHAIN_FILE=/vcpkg/scripts/buildsystems/vcpkg.cmake)


CMD ["bash"]