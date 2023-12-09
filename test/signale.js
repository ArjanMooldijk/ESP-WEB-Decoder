const typeSignalen = `
[
     {
          "sigType": "Vor2",
          "sigHoofdtype": "voorsein",
          "sigComment": "Voorsein 2 draden",
          "sigNbrAdr": 2,
          "sigAdrType": [
               "VorAdr1",
               "VorAdr2Dkl"
          ],
          "sigBeelden": [
               "Warnung",
               "Fb1",
               "Dunkel"
          ],
          "sigDraden": 2,
          "sigImage": "/Vor2"
     },
     {
          "sigType": "Vor4",
          "sigHoofdtype": "voorsein",
          "sigComment": "Voorsein 4 draden",
          "sigNbrAdr": 3,
          "sigAdrType": [
               "VorAdr1",
               "Vor2Adr",
               "VorAdr3Dkl"
          ],
          "sigBeelden": [
               "Warnung",
               "Fb1",
               "Fb2",
               "Fb3",
               "Dunkel"
          ],
          "sigDraden": 4,
          "sigImage": "/Vor4"
     },
     {
          "sigType": "Vors5",
          "sigHoofdtype": "voorsein",
          "sigComment": "Voorsein 5 draden",
          "sigNbrAdr": 3,
          "sigAdrType": [
               "VorAdr1",
               "Vor2Adr",
               "VorAdr3Dkl"
          ],
          "sigBeelden": [
               "Warnung",
               "Fb1",
               "Fb2",
               "Fb3",
               "Fb5",
               "Dunkel"
          ],
          "sigDraden": 5,
          "sigImage": "/Vor5"
     },
     {
          "sigType": "H2gr",
          "sigHoofdtype": "hoofdsein",
          "sigComment": "Hoofdsein 2 draden",
          "sigNbrAdr": 1,
          "sigAdrType": [
               "HptAdr1"
          ],
          "sigBeelden": [
               "Halt",
               "Fb1"
          ],
          "sigDraden": 2,
          "sigImage": "/H2gr"
     },
     {
          "sigType": "H3gro",
          "sigHoofdtype": "hoofdsein",
          "sigComment": "Hoofdsein 3 draden: groen, rood, oranje",
          "sigNbrAdr": 2,
          "sigAdrType": [
               "HptAdr1",
               "HptAdr2O"
          ],
          "sigBeelden": [
               "Halt",
               "Fb1",
               "Fb2"
          ],
          "sigDraden": 3,
          "sigImage": "/H3gro"
     },
     {
          "sigType": "H3grg",
          "sigHoofdtype": "hoofdsein",
          "sigComment": "Hoofdsein 3 draden: groen, rood, groen",
          "sigNbrAdr": 2,
          "sigAdrType": [
               "HptAdr1",
               "HptAdr2G"
          ],
          "sigBeelden": [
               "Halt",
               "Fb1",
               "Fb3"
          ],
          "sigDraden": 3,
          "sigImage": "/H3grg"
     },
     {
          "sigType": "H4grog",
          "sigHoofdtype": "hoofdsein",
          "sigComment": "Hoofdsein 4 draden: groen, rood, oranje, groen",
          "sigNbrAdr": 2,
          "sigAdrType": [
               "HptAdr1",
               "HptAdr2OG"
          ],
          "sigBeelden": [
               "Halt",
               "Fb1",
               "Fb2",
               "Fb3"
          ],
          "sigDraden": 4,
          "sigImage": "/H4grog"
     },
     {
          "sigType": "H4goro",
          "sigHoofdtype": "hoofdsein",
          "sigComment": "Hoofdsein 4 draden: groen oranje, rood, oranje",
          "sigNbrAdr": 2,
          "sigAdrType": [
               "HptAdr1",
               "HptAdr2OO"
          ],
          "sigBeelden": [
               "Halt",
               "Fb1",
               "Fb2",
               "Fb6"
          ],
          "sigDraden": 4,
          "sigImage": "/H4goro"
     },
     {
          "sigType": "H5grgog",
          "sigHoofdtype": "hoofdsein",
          "sigComment": "Hoofdsein 5 draden: groen, rood, groen, oranje, groen",
          "sigNbrAdr": 3,
          "sigAdrType": [
               "HptAdr1",
               "HptAdr2GO",
               "HptAdr3G"
          ],
          "sigBeelden": [
               "Halt",
               "Fb1",
               "Fb2",
               "Fb3",
               "Fb5"
          ],
          "sigDraden": 5,
          "sigImage": "/H5grgog"
     },
     {
          "sigType": "H5grogo",
          "sigHoofdtype": "hoofdsein",
          "sigComment": "Hoofdsein 5 draden: groen, rood, oranje, groen, oranje",
          "sigNbrAdr": 3,
          "sigAdrType": [
               "HptAdr1",
               "HptAdr2OG",
               "HptAdr3O"
          ],
          "sigBeelden": [
               "Halt",
               "Fb1",
               "Fb2",
               "Fb3",
               "Fb6"
          ],
          "sigDraden": 5,
          "sigImage": "/H5grogo"
     },
     {
          "sigType": "H7gogor",
          "sigHoofdtype": "hoofdsein",
          "sigComment": "Hoofdsein 5 draden: groen oranje, groen, oranje, rood (7-licht)",
          "sigNbrAdr": 3,
          "sigAdrType": [
               "HptAdr1",
               "HptAdr2GO",
               "HptAdr3O"
          ],
          "sigBeelden": [
               "Halt",
               "Fb1",
               "Fb2",
               "Fb3",
               "Fb6"
          ],
          "sigDraden": 5,
          "sigImage": "/H7gogor"
     },
     {
          "sigType": "H7ggogr",
          "sigHoofdtype": "hoofdsein",
          "sigComment": "Hoofdsein 5 draden: groen, groen, oranje, groen, rood (7-licht)",
          "sigNbrAdr": 3,
          "sigAdrType": [
               "HptAdr1",
               "HptAdr2GO",
               "HptAdr3G"
          ],
          "sigBeelden": [
               "Halt",
               "Fb1",
               "Fb2",
               "Fb3",
               "Fb5"
          ],
          "sigDraden": 5,
          "sigImage": "/H7ggogr"
     },
     {
          "sigType": "H7gogogr",
          "sigHoofdtype": "hoofdsein",
          "sigComment": "Hoofdsein 6 draden: groen, oranje, groen, oranje, groen, rood (7-licht)",
          "sigNbrAdr": 3,
          "sigAdrType": [
               "HptAdr1",
               "HptAdr2GO",
               "HptAdr3GO"
          ],
          "sigBeelden": [
               "Halt",
               "Fb1",
               "Fb2",
               "Fb3",
               "Fb5",
               "Fb6"
          ],
          "sigDraden": 6,
          "sigImage": "/H7gogogr"
     },
     {
          "sigType": "Zwerg",
          "sigHoofdtype": "overig",
          "sigComment": "Dwergsein",
          "sigNbrAdr": 2,
          "sigAdrType": [
               "ZwergAdr1",
               "ZwergAdr2"
          ],
          "sigBeelden": [
               "Halt",
               "Fahrt",
               "Warnung"
          ],
          "sigDraden": 3,
          "sigImage": "/Zwerg"
     },
     {
          "sigType": "SIMV",
          "sigHoofdtype": "overig",
          "sigComment": "Simplon Inter Modal voorsein",
          "sigNbrAdr": 1,
          "sigAdrType": [
               "SIMVor"
          ],
          "sigBeelden": [
               "Halt",
               "Fahrt"
          ],
          "sigDraden": 1,
          "sigImage": "/SIM Vor"
     },
     {
          "sigType": "SIMH",
          "sigHoofdtype": "overig",
          "sigComment": "Simplon Inter Modal hoofdsein",
          "sigNbrAdr": 1,
          "sigAdrType": [
               "SIMHaupt"
          ],
          "sigBeelden": [
               "Halt",
               "Fahrt"
          ],
          "sigDraden": 1,
          "sigImage": "/sim"
     },
     {
          "sigType": "HbB",
          "sigHoofdtype": "overig",
          "sigComment": "Halt bei Bedarf",
          "sigNbrAdr": 1,
          "sigAdrType": [
               "HbB"
          ],
          "sigBeelden": [
               "Halt",
               "Fahrt"
          ],
          "sigDraden": 1,
          "sigImage": "/Bedarf-Halt"
     },
     {
          "sigType": "FSM",
          "sigHoofdtype": "overig",
          "sigComment": "Fahrtstellungsmelder",
          "sigNbrAdr": 1,
          "sigAdrType": [
               "FSM"
          ],
          "sigBeelden": [
               "Halt",
               "Fahrt"
          ],
          "sigDraden": 1,
          "sigImage": "/fsm"
     },
     {
          "sigType": "Lmp",
          "sigHoofdtype": "lamp",
          "sigComment": "1 of meer lampen op 1 adres",
          "sigNbrAdr": 1,
          "sigAdrType": [
               "Lmp"
          ],
          "sigBeelden": [
               "Aus",
               "Ein"
          ],
          "sigDraden": 1,
          "sigImage": "/lamp"
     }
]`;