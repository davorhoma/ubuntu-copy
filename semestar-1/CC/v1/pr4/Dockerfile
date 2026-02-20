FROM python:3.12-alpine
WORKDIR /app
COPY . .
ENTRYPOINT ["python3"]
CMD ["rng.py"]

# 1: docker build -t v1-primer4 .
# 2: docker run --name igrica -it v1-primer4
# 3: docker stop igrica
# 4: docker run --name igrica2 --rm -it v1-primer4
# 5: docker stop igrica2
# docker rm igrica