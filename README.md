Installation

Be aware that you need to pre-install docker. (You will have locally database stored in /var/lib/docker/volumes/rent-tracking-database/)
```
git clone https://github.com/EgorPalysaev/Rent-Tracking-Database.git
cd Rent-Tracking-Database/src/
docker image build -t egorpalysaev/rent-tracking-database .
docker buildx prune
docker run -ti --name rent-tracking-database -v rent-tracking-database:/usr/locale/bin/database egorpalysaev/rent-tracking-database
```
To run container: ```docker start -ai rent-tracking-database```

To stop and remove container: ```docker stop rent-tracking-database && docker rm rent-tracking-database```

To remove volume: ```docker volume rm rent-tracking-database```

If you want to save builder docker-image run: ```docker image build --target builder -t egorpalysaev/rent-tracking-database-builder .```

Or you can download container from docker-hub: ```docker pull egorpalysaev/rent-tracking-database:latest```

If you have pre-installed GCC/Clang compiler and SQLite, you can simply run: ```make app```

You can change compiler by run (default = gcc): ```make CC=clang```
