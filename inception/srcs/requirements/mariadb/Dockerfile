FROM alpine:3.16

RUN apk update && apk add mariadb mariadb-client


EXPOSE 3306

COPY ./tools/run_db.sh /usr/local/bin
RUN chmod a+x /usr/local/bin/run_db.sh

RUN mkdir -p /var/run/mysqld \
&& chown -R mysql:mysql /var/run/mysqld \
&& chmod 777 /var/run/mysqld

CMD ["/usr/local/bin/run_db.sh"]