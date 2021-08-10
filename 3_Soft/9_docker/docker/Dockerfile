FROM ubuntu

RUN apt update -y
COPY "./a.out" "/a.out"
RUN chmod a+x /a.out
CMD [ "/a.out" ]
