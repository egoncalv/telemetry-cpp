## Running MQTT Broker with Docker
    docker run -d --name emqx -p 1883:1883 -p 8083:8083 -p 8883:8883 -p 18083:18083 emqx/emqx:latest
