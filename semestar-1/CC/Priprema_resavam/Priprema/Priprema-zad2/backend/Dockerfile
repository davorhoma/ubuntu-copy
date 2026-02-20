FROM python:3.10
WORKDIR /app
COPY . .
RUN pip install -r requirements.txt
EXPOSE 9000
RUN chmod +x /app/skripta.sh
ENTRYPOINT ["/app/skripta.sh"]
# ENTRYPOINT ["python3", "manage.py"]
# ENTRYPOINT ["python3"]
# CMD ["manage.py"]
