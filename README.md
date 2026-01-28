# advanced-os-zephyr


## Docker image for zephyr
docker pull modularmx/zephyros:latest

In your local machine choose a directory where your project and Zephyr source code will live. Run the container with a shared folder using the --mount flag. And in my case the /home/user/workspace set the working folder inside my container.

docker run -it --rm -w /home/user/workspace --mount type=bind,src="$(pwd)",dst=/home/user/workspace modularmx/zephyros:latest


Once the container is running you can run the west tool to download Zephyr from its official repositories. This is going to take a while because it will download the entire project!!, something we should avoid using a manifest, but fort the “momento” I think is worthy.

west init
west update


Build your project using west. -p always means make a new build directory (or rewrite the existing one), while app is the name of the directory with the source files. If you want to remove the compilation binaries for wherever reason just type west build -t pristine

## Build the app
west build -p always app

or

west build -p always -b qemu_x86 applications/app1

or

west build -p always -b native_sim applications/app1

## Run the app
west build -t run 
