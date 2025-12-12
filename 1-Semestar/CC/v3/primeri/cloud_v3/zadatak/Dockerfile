FROM python:3.8
WORKDIR /app
COPY . /app
RUN pip install -r /app/requirements.txt
RUN python3 manage.py migrate

EXPOSE "8081"
ENTRYPOINT ["python3"]
CMD ["manage.py", "runserver", "0.0.0.0:8081"]