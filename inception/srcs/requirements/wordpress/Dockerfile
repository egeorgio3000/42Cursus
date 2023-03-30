FROM alpine:3.16

# Install necessary packages
RUN apk update ; \
    apk upgrade ; \
    apk add --no-cache \
    php$PHP_VERSION \
    php$PHP_VERSION-fpm \
    php$PHP_VERSION-mysqli \
    php$PHP_VERSION-json \
    php$PHP_VERSION-phar \
    php$PHP_VERSION-zlib \
    php$PHP_VERSION-gd \
    php$PHP_VERSION-curl \
    php$PHP_VERSION-mbstring \
    php$PHP_VERSION-xml \
    php$PHP_VERSION-openssl \
    curl \
    tar 

RUN apk add --no-cache mariadb-client \
    mysql-client \

# Download and install WordPress
RUN mkdir /var/www && \
    mkdir /var/www/html

#RUN chown -R www-data:www-data /var/www/html
RUN chmod -R 755 /var/www/html

COPY ./conf/php-fpm.conf /etc/php8/php-fpm.d/zzz_custom.conf

COPY ./tools/run_wp.sh /usr/local/bin
RUN chmod +x /usr/local/bin/run_wp.sh
# Expose port for WordPress
EXPOSE 9000

WORKDIR /var/www/html

# Start PHP-FPM server
CMD ["/usr/local/bin/run_wp.sh"]
