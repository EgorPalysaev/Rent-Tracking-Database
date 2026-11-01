Installation

Be aware that you need to pre-install docker. (You will have locally database stored in /var/lib/docker/volumes/rent-tracking-database/)
```
git clone https://github.com/EgorPalysaev/RenTrack.git
cd RenTrack/src/
docker image build -t egorpalysaev/rent-tracking-database .
docker buildx prune
docker run -ti -v rent-tracking-database:/usr/locale/bin/database egorpalysaev/rent-tracking-database
```
If you want to save builder docker-image run: ```docker image build --target builder -t egorpalysaev/rent-tracking-database-builder .```

Or you can download container from docker-hub ```docker pull egorpalysaev/rent-tracking-database```

If you have pre-installed GCC/Clang compiler and SQLite, you can simply run: ```make app```

You can change compiler by run (default = gcc): ```make CC=clang```
