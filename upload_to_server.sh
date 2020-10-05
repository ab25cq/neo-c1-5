#!/bin/bash

make distclean

(cd ..; tar cvfz neo-c2.tgz neo-c2)
(cd ..; scp neo-c2.tgz ab25cq@clover-lang.org:)
ssh ab25cq@clover-lang.org bash -c '"cp -f neo-c2.tgz repo/; cd repo; rm -rf neo-c2; tar xvfz neo-c2.tgz"'

