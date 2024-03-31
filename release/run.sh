# it will works with no running containers in this server
# and Docker has default network addresses, begins from 172.17.0.2
# build containers need more parameters for orchestration

# first emqx in background - other way it blocks console
docker run emqx &
sleep 5

# run container based on poetgreSql,  
docker run --name db-data-analysis -e POSTGRES_PASSWORD=123456 -d postgres &
sleep 5

# build & run web server mqtt producer container 
cd docker_nonqt01
docker run $(docker build -q ./) &
sleep 5

# build & run mqtt producer & db writer container
cd ../docker_server
docker run $(docker build -q ./) &
sleep 5

echo "Now send GET, POST & DELETE commands to 172.17.0.4:1234/count for testing"

# close it manually
wait
