#!/bin/sh

if [ -f ./wp_config]
then
    echo "wordpress already installed"
else

    # Download and instal wp-CLI

    curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
    chmod +x wp-cli.phar
    mv wp-cli.phar /usr/local/bin/wp


    # config wp-config.php + wp - CLI
    wp core download --path=/var/www/html --extract=true --allow-root
    sed -i "s/database_name_here/$WP_DATABASE_NAME/g" wp-config-sample.php
    sed -i "s/password_here/$MYSQL_PASSWORD/g" wp-config-sample.php
    sed -i "s/username_here/$MYSQL_USER/g" wp-config-sample.php
    sed -i "s/localhost/$MYSQL_HOST/g" wp-config-sample.php
    cp wp-config-sample.php wp-config.php
    wp core install --url=$DOMAIN_NAME --title="$WP_TITLE" --admin_user=$WP_ADMIN --admin_password=$WP_ADMIN_PASSWORD --admin_email=$WP_ADMIN_EMAIL --skip-email --allow-root
	wp user create $WP_USER $WP_USER_EMAIL --role=$WP_USER_ROLE --user_pass=$WP_USER_PASSWORD --allow-root

fi

echo "wordpress ready to use"

exec php-fpm$PHP_VERSION -F -R
