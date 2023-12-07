cmd_/home/leonidsah/Desktop/scull_driver/scull.mod := printf '%s\n'   scull.o | awk '!x[$$0]++ { print("/home/leonidsah/Desktop/scull_driver/"$$0) }' > /home/leonidsah/Desktop/scull_driver/scull.mod
