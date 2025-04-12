FROM ubuntu:24.04

WORKDIR /opt/

RUN apt-get update && apt-get install -y openssh-server \
    && mkdir /var/run/sshd

RUN useradd -m myuser && echo "myuser:mypassword" | chpasswd

# Дозволити логін по паролю (НЕ для продакшену!)
RUN sed -i 's/^#PasswordAuthentication yes/PasswordAuthentication yes/' /etc/ssh/sshd_config

# Відкрити порт
EXPOSE 22

COPY ./workers ./workers 
COPY ./script.sh ./script.sh 

RUN chmod +x script.sh

CMD ["/opt/script.sh"]
