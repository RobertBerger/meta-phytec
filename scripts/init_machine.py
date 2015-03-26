#!/usr/bin/env python2
# -*- coding: utf-8 -*-
# Copyright 2015, PHYTEC Messtechnik GmbH
# Author: Stefan Müller-Klieser <s.mueller-klieser@phytec.de>

from switch_machine import *


def main():
    bsp = BSP_Switcher()
    if not bsp.selected_machine:
        # we could not parse a machine from manifest xml
        # we assume we set up an unified bsp and need to
        # ask the user for a machine to be set up
        bsp.switch_machine()
    bsp.write_machine_to_localconf()

if __name__ == "__main__":
    main()
