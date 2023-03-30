FROM alpine:3.16

RUN apk add --update nginx openssl \
  && rm -rf /var/cache/apk/* 

RUN mkdir /etc/nginx/ssl
# create a self-signed SSL/TLS certificate for the nginx web server.
RUN openssl req -x509 -newkey rsa:4096 -keyout /etc/nginx/ssl/server.key -out /etc/nginx/ssl/server.crt -days 365 -nodes -subj '/CN=localhost' 
COPY ./conf/nginx.conf /etc/nginx/nginx.conf
EXPOSE 443 

CMD ["nginx", "-g", "daemon off;"]