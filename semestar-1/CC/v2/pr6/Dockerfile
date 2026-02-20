ARG PYTHON_VERSION=3.9-slim
FROM python:${PYTHON_VERSION}
WORKDIR /app
COPY . /app
LABEL ime="app6" student="Davor Homa"
ENV GREETING="Hello, Docker!"
ENTRYPOINT ["python"]
CMD ["app6.py"]