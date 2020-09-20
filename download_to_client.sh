#!/bin/bash

ssh ab25cq@clover-lang.org bash -c '"rm -f neo-c2.tgz; cd repo/neo-c2; make distclean; cd ..; tar cvfz ~/neo-c2.tgz neo-c2"'
cd ..; rm -rf neo-c2
scp ab25cq@clover-lang.org:neo-c2.tgz .
tar xvfz neo-c2.tgz
cd .

