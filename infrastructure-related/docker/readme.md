# Docker vs Virtual Machine
## Operating system
an OS has 2 layers: `kernal` and `applications`. 1) the kernal runs on top of the hardware; 2) applications layer runs on top of kernal.

ubuntu, linux mint etc, all run on top of a linux kernal, but the difference btw them is the application layer.

## what they virtualise
docker and virtual machines are both virtualization tools. so what parts of the OS do they virtualise?

- docker virtualises the `applications` layer. and it uses the kernal of the machine it is running on.
- virtual machine virtualises both `kernal` and `applications` layer.

what does this mean? because docker images only concern with applications, they:
- are much smaller
- start and run faster
- might not be compatible with all OS kernals. virtual machines are compatible with all. installing docker actually depends on your version of windows / mac! not all OS can run docker natively.

# Docker Terminology
## Docker Image
Images are read-only templates containing instructions for creating a container. A Docker image creates containers to run on the Docker platform.

An image is composed of multiple stacked layers, like layers in a photo editor, each changing something in the environment. Images contain the code or binary, runtimes, dependencies, and other filesystem objects to run an application. The image relies on the host operating system (OS) kernel.

For example, to build a web server image, start with an image that includes Ubuntu Linux (a base OS). Then, add packages like Apache and PHP on top.

You can manually build images using a Dockerfile, a text document containing all the commands to create a Docker image. You can also pull images from a central repository called a registry, or from repositories like Docker Hub

When a Docker user runs an image, it BECOMES one or multiple container instances.

source: https://circleci.com/blog/docker-image-vs-container/
## Docker Container
It is NOT the same as the image, which are the files you pass around. You execute the image IN the container. The docker container is an isolated environment that you run applications in.

Think of a Docker container as a running image instance. You can create many containers from the same image, each with its own unique data and state.

source: https://circleci.com/blog/docker-image-vs-container/

images are what we share, NOT the container.

## Docker network
docker manages networks as well. containers in the same isolated network can communicate with each other easily via container name.

## why use a container
### development
Before containers, say if a team were to work on an application involving postgres, redis etc. They have to install those binaries on each of their development machine (some using mac, some using linux etc). There are many steps where things can go wrong, and it can be very tedious too.

this is not a problem for containers as it runs in an isolated environment and should work the same for most machines.

### deployment
before containers, the development team will create a set of artifacts and instructions on how to install and configure them on the server. this will be passed to the operations team to handle. not good as:
- the installation is done directly on the OS, which could lead to conflict errors with dependencies, multiple instances etc.
- there could be miscom between development team and operation team. unneeded back and forth

this is not a problem for containers as the start script always works the same way in its own isolated env.

# Using Docker
https://docs.docker.com/engine/reference/commandline/docker/

## general use
- `docker pull <image name>` # pulls things from docker hub
- `docker images` # view all images
- `docker ps` # view all running containers
- `docker ps -a` # view all containers (running and exited)
- `docker network ls` # view all networks

# running containers
- `docker run <image name>` # starts a new container
- `docker run -d <image name>` # starts a new container IN DETACHED MODE!
- `docker run -p <host port>:<container port> <image name>` # starting a container with port binding (more info on that below!)
- `docker run -e <environment var> -e <env var 2> <image name>` # define any number of env var u want
- `docker run --network <network name> <image name>` # run container in a network
- `docker stop <container id>` # stop container
- `docker start <container id>` # starts a container that has been previously stopped

# managing networks
- `docker network create <network name>` # create a new docker network

# debugging
- `docker logs <container id>` # to view the logs of the container
- `docker exec -it <container id> /bin/bash` # starts up interactive terminal ("-it") for container
- `exit` # to leave "it" mode

# deleting stuff
- `docker rm <container id>` # to delete stopped containers
- `docker rmi <image id>`  # to delete images

# tidbit on container port vs host port
```
CONTAINER ID   IMAGE     COMMAND                  CREATED         STATUS         PORTS      NAMES
564af79fb065   redis     "docker-entrypoint.s…"   7 minutes ago   Up 3 seconds   6379/tcp   charming_euclid
```
when running `docker ps` the above example shows a redis container, listening to port 6379.

many containers can run on host machine, but our laptop has only certain ports available.

the question comes here... when running `docker ps`, will i ever see 2 containers listening to same port? answer is YES! but how is this possible? isn't there a conflict?

```
CONTAINER ID   IMAGE     COMMAND                  CREATED          STATUS         PORTS      NAMES
08683c35f346   redis     "docker-entrypoint.s…"   3 seconds ago    Up 2 seconds   6379/tcp   musing_lamport
564af79fb065   redis     "docker-entrypoint.s…"   17 minutes ago   Up 9 minutes   6379/tcp   charming_euclid
```
just run `docker run redis` twice! 2 containers are created!

Well there is a difference between container port vs host port. docker maintains a mapping between the port on the host machine to the port that the container is listening to! This is simply port binding.

**so 6379/tcp is NOT a port opened on your local machine! its a "container port".**

how to do port binding? `docker run -p 6000:6379 redis`!

```
CONTAINER ID   IMAGE     COMMAND                  CREATED         STATUS         PORTS                    NAMES
f20c92501f4d   redis     "docker-entrypoint.s…"   3 seconds ago   Up 2 seconds   0.0.0.0:6000->6379/tcp   friendly_albattani
```

now our host machine's port 6000 is binded to container f20c92501f4d's port 6379!

# docker compose
lets say there is a specific set of commands that you always have to run like
```
docker network create mongo-network

docker run -d ....... mongo

docker run -d ....... mongo-express
```
for ease of running all the above commands easily and exactly the same each time, we can map the above commands into a `docker compose` yml file.

sample command would be:
- `docker-compose -f <filename>.yml up -d` # to run the file
- `docker-compose -f <filename>.yml down -d` # to stop all containers created with yml (and delete any created networks)

notes:
- `docker compose` automatically creates a common network for the containers it creates.
- `docker compose` runs the commands at the same time. you have to add additional logic to make commands wait for each other (if you require them to be in order)

# dockerfile
sequence of instructions on how to build an image. example of what a docker file looks like:
```
FROM node  # basing our image off a node image from dockerhub (node already installed)

ENV MONGO_DB_USERNAME=admin MONGO_DB_PWD=password

RUN mkdir -p /home/app  # RUN allows you to execute any linux commands WITHIN the container

COPY . /home/app  # executes on the HOST machine. basically allows me to copy files in host machine into the image

CMD ["node", "/home/app/server.js"]  # start the app with "node server.js" in the container.
```

`CMD` vs `RUN`. both run linux commands, but `CMD` is an entry point command. you can have many `RUN` commands, but you should just have 1 `CMD` command as an entry point.

each image on dockerhub should also be created from their own respective dockerfiles too. for example: [here](https://github.com/nodejs/docker-node/blob/main/16/buster/Dockerfile)

## image layers
From here it is also apparent how images are built on top of each other (hence many ppl refer to them as image layers)
the above dockerfile would produce an image that can be referred to as `app:1.0`. `app:1.0` built on `node`, built on `alpine`.

notes:
- dockerfile must be saved as `Dockerfile`, no file extension.

to build the image, `docker build -t my-app:1.0 .` (1st arg is the tag: "my-app:1.0". 2nd arg is path to dockerfile. hence '.' is used)

the image can also be pushed to a public/private docker repository if necessary.

## flow for sharing
- typically, dockerfile will be version controlled on git, available for team members to `git pull`
- images will be shared in a public/private repository (like AWS ECR), available for team members to `docker pull`
- since image is in a team accessible repo, it can be included in docker compose as well for ease of integration

# docker volumes
Volumes are the preferred mechanism for persisting data generated by and used by Docker containers. 

a docker container would have a `virtual` file system. when the container is stopped or removed, `virtual` file system (which includes the data) is lost.

the way volumes work is to `bind` the `host/physical` file system with the `virtual` file system. any changes made on either file systems can then be replicated to each other. when the container stops running, the `host/physical` file system is still there :)

3 types of volumes:
- host volumes
  - define which location on host machine to mount
  - `docker run -v <host dir>:<container dir>`, e.g.: `docker run -v /home/mount/data:/var/lib/mysql/data`
- anonymous volumes
  - docker decides for you. most likely `/var/lib/docker/volumes/random-hash/_data`
  - `docker run -v <container dir>`
- named volumes
  - slight improvement over anonymous. we decide the name of the folder on the host machine
  - `docker run -v <folder name>:<container dir>`, e.g: `docker run -v name:/var/lib/mysql/data`