USER = egeorgio
SRC = ./srcs/docker-compose.yml

all:
	@ mkdir -p /home/$(USER)/data/wp
	@ mkdir -p /home/$(USER)/data/db
	@ if ! grep -q "127.0.0.1 $(USER).42.fr" /etc/hosts; then  \
		echo "127.0.0.1 $(USER).42.fr" >> /etc/hosts; \
	fi

	@docker-compose -f $(SRC) build
	@docker-compose -f $(SRC) up -d

stop:
	@docker-compose -f $(SRC) stop

clean:
	@ docker-compose -f $(SRC) down

fclean: clean
	@- docker volume rm $$(docker volume ls -q)
	@ rm -rf /home/$(USER)/data/wp
	@ rm -rf /home/$(USER)/data/db
	@ docker system prune -af > /dev/null

re: fclean all