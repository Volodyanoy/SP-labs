FROM amazonlinux:2

RUN yum update -y && \
    yum install -y file && \
    yum install -y coreutils && \
    yum clean all

COPY script_rvs_7491.sh /script_rvs_7491.sh

RUN chmod +x /script_rvs_7491.sh

CMD ["/script_rvs_7491.sh"]
