FROM debian:bookworm

RUN apt update && apt install -y git cmake ninja-build clang flex bison zlib1g-dev libcurl4-openssl-dev

# Compile with clang
ENV CC=clang
ENV CXX=clang++

# Clone the repository
RUN mkdir -p /tmp/openmohaa/build \
    && cd /tmp/openmohaa \
    && git clone --depth 1 --single-branch -b main https://github.com/openmoh/openmohaa.git

# Build the project
RUN cd /tmp/openmohaa/build \
    && cmake -G "Ninja" -DBUILD_NO_CLIENT=1 -DCMAKE_BUILD_TYPE="RelWithDebInfo" -DTARGET_LOCAL_SYSTEM=1 -DCMAKE_INSTALL_PREFIX="/usr/local/games/openmohaa" /tmp/openmohaa/openmohaa \
    && cmake --build . \
    && cmake --install .

# Reset to the base debian image, will gain space
FROM debian:bookworm

# Copy the installed directory
COPY --from=0 /usr/local/games/openmohaa /usr/local/games/openmohaa

# MOHAA data (main, mainta and maintt) goes inside this directory
# mods can go inside a subdirectory called "home"
VOLUME "/usr/local/share/mohaa"

# Install tools to check for the health
RUN apt update && apt install -y socat libcurl4-openssl-dev
COPY "health_check.sh" "/usr/local/bin/health_check.sh"
HEALTHCHECK --interval=15s --timeout=20s --start-period=10s --retries=3 CMD [ "bash", "/usr/local/bin/health_check.sh" ]

# Create an user for starting the server
# This improves the overall security of the server instance
RUN useradd -m openmohaa
USER openmohaa

ENV GAME_PORT=12203
ENV GAMESPY_PORT=12300

COPY "entrypoint.sh" "/usr/local/bin/entrypoint.sh"
WORKDIR "/usr/local/share/mohaa"

ENTRYPOINT [ "bash", "entrypoint.sh" ]
