$(function () {

    // $(".signal-types").hide();

    // Get base dekoder data
    //----- weg voor prod
    getDatafromServer(); // comment voor test

    var saveOldVal = {
        fade: null,
        dark: null,
        lamp: []
    };
    var changedValues = false;
    var bdelWasVisibale;
    var signalToChange;
    var dekoder;
    var deKoder; // comment voor test
    var typeSig;
    //================================
    // Voor testen:
    // console.log(deKoder);
    // dekoder = JSON.parse(deKoder);
    // // console.log(dekoder);
    // typeSig = JSON.parse(typeSignalen);
    // // //////////// Build main screen
    // makeHeader();
    // makeMainScreen();
    // setEvents();
    //================================
    var socket;
    initSocket(); // comment voor test

    function getDatafromServer() {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
            if (this.readyState == 4 && this.status == 200) {
                deKoder = this.responseText;
                // console.log(deKoder);
                dekoder = JSON.parse(deKoder);
                // console.log(dekoder);
                typeSig = JSON.parse(typeSignalen);
                //////////// Build main screen
                makeHeader();
                makeMainScreen();
                setEvents();
            } else if (this.status > 200) {
                console.log('get from server failed');
                console.log(this.status);
            }
        };
        xhttp.open("GET", "/GetDecVal", true);
        xhttp.send();
    };

    function initSocket() {
        socket = new WebSocket('ws://' + window.location.hostname + ':81/');
        socket.onmessage = function (event) {
            processSockEvent(event);
        }
    };

    function processSockEvent(event) {
        console.log(event.data);
    };

    function getObjects(obj, key, val) {
        var objects = [];
        for (var i in obj) {
            if (!obj.hasOwnProperty(i)) continue;
            if (typeof obj[i] == 'object') {
                objects = objects.concat(getObjects(obj[i], key, val));
            } else if (i == key && obj[key] == val) {
                objects.push(obj);
            }
        }
        return objects;
    };
    function setEvents() {
        $('.Mainbuttoncontainer').delegate('#BNew', 'click', newSignal);
        $('.Mainbuttoncontainer').delegate('#BStore', 'click', _storeValues);
        $('#connectedSignal').delegate('.sigBut', 'click', _changeSig);
        $('#changeSignal').delegate('input.slider', 'input', showSliderVal);
        $('.adrescontainer').delegate('#adres1', 'input', _filladressVal);
        $('.ChangeButtoncontainer').delegate('#BCancelC', 'click', _cancelKeuzeC);
        $('.ChangeButtoncontainer').delegate('#BDel', 'click', _deleteSignal);
        $('.ChangeButtoncontainer').delegate('#BApply', 'click', _processChange.bind(this));
        $('#allTypeSeinen').delegate('input:radio[name=sigGekozen]', 'click', _showAdresInput);
        $('#signal-config').delegate('input.slider', 'input', showSliderVal);
        $('.NewButtoncontainer').delegate('#BKeuze', 'click', _processKeuze);
        $('.NewButtoncontainer').delegate('#BCancelN', 'click', _cancelKeuzeN);
    };

    function _filladressVal() {
        var aantal;
        var a1, a2, a3;
        a1 = parseInt($("#adres1").val());
        if ($('#adres2').is(':visible')) {
            if ($('#adres3').is(':visible')) {
                //vul tweede en derde adres
                a2 = a1 + 1;
                $('#adres2').val(String(a2));
                a3 = a2 + 1;
                $('#adres3').val(String(a3));
            } else {
                //vul tweede en derde adres
                a2 = a1 + 1;
                $('#adres2').val(String(a2));
            }
        }
    }

    function _storeValues() {
        //doe post naar server
        changedValues = false;
        $(".storebutton").hide();
        const xhr = new XMLHttpRequest();

        // listen for `load` event
        xhr.onload = () => {
            // print JSON response
            if (xhr.status >= 200 && xhr.status < 300) {
                // parse JSON
                // const response = JSON.parse(xhr.responseText);
                console.log(xhr.responseText);
            }
        };

        // create a JSON object
        const jsonDekoder = JSON.stringify(dekoder);
        console.log(jsonDekoder);

        // open request
        xhr.open("POST", "/PostDecVal");

        // set `Content-Type` header
        xhr.setRequestHeader('Content-Type', 'application/json');

        // send rquest with JSON payload
        xhr.send(jsonDekoder);
        // xhr.send(JSON.stringify(jsonDekoder));

    };

    function _changeSig() {
        changeSignal($(this).attr('id'));
    };

    function _cancelKeuzeC() {
        dekoder.sigConnected[signalToChange.sigId].sigLamp = saveOldVal.lamp;
        dekoder.sigConnected[signalToChange.sigId].sigFade = saveOldVal.fade;
        dekoder.sigConnected[signalToChange.sigId].sigDark = saveOldVal.dark;
        makeHeader();
        makeMainScreen();
    };

    function _deleteSignal() {
        dekoder.sigConnected.pop();
        dekoder.nbrofsig--;
        changedValues = true;
        makeHeader();
        makeMainScreen();
    };

    function _processChange() {
        var i = signalToChange.sigId;
        var $el = ('#changeForm');
        // dekoder.sigConnected[i].sigFade = $(this).find('#fade').next('.sout').html() * 10;
        // dekoder.sigConnected[i].sigDark = $(this).find('#dark').next('.sout').html() * 10;
        dekoder.sigConnected[i].sigFade = $($el).find('#fade').next('.sout').html();
        dekoder.sigConnected[i].sigDark = $($el).find('#dark').next('.sout').html();

        var tmpLamp = $('.lampInput');
        $.each(tmpLamp, function (count, item) {
            dekoder.sigConnected[i].sigLamp[count] = $(item).val();
        });
        changedValues = true;
        makeHeader();
        makeMainScreen();
    };

    function showSliderVal() {
        var $el = ('#sigKeuze');
        var subject = {
            sigId: signalToChange.sigId,
            sigFade: 0,
            sigDark: 0,
            sigLamp: []
        };
        subject.sigFade = $($el).find('#fade').next('.sout').html();
        subject.sigDark = $($el).find('#dark').next('.sout').html();

        var tmpLamp = $('.lampInput');
        $.each(tmpLamp, function (count, item) {
            subject.sigLamp[count] = $(item).val();
        });
        return $(this).each(function () {
            switch ($(this).attr("id")) {
                case "fade":
                    var value = $(this).val() * 10;
                    subject.sigFade = value;
                    break;
                case "dark":
                    var value = $(this).val() * 10;
                    subject.sigDark = value;
                    break;
                case "lamp1":
                    var value = $(this).val();
                    subject.sigLamp[0] = value;
                    break;
                case "lamp2":
                    var value = $(this).val();
                    subject.sigLamp[1] = value;
                    break;
                case "lamp3":
                    var value = $(this).val();
                    subject.sigLamp[2] = value;
                    break;
                case "lamp4":
                    var value = $(this).val();
                    subject.sigLamp[3] = value;
                    break;
                case "lamp5":
                    var value = $(this).val();
                    subject.sigLamp[4] = value;
                    break;
                case "lamp6":
                    var value = $(this).val();
                    subject.sigLamp[5] = value;
            }
            $(this).next("#sout").html(value);

            // create a JSON object
            const jsonSubject = JSON.stringify(subject);
            socket.send(jsonSubject);
            console.log(jsonSubject);

        })
    };

    function _showAdresInput() {
        var value = $(this).val();
        seinType = "";
        seinType = $(this).attr('id');
        if (value == 1) {
            $(".2adres").hide();
            $(".3adres").hide();
            $(".1adres").show();
        } else {
            if (value == 2) {
                $(".1adres").hide();
                $(".3adres").hide();
                $(".2adres").show();
            } else {
                $(".1adres").hide();
                $(".2adres").hide();
                $(".3adres").show();
            }
        }
        if (seinType == 'Lamp') {
            $(".lampnbr").show();
            $(".fade").hide();
            $(".dark").hide();
        }
        else {
            $(".lampnbr").hide();
            $(".fade").show();
            $(".dark").show();
        }
        $(".instellingen").show();
    };

    function _processKeuze() {
        var tmpFade;
        var tmpDark;
        var selSignalType = getObjects(typeSig, 'sigType', seinType);
        if (seinType == 'Lamp') {
            selSignalType[0].sigDraden = parseInt($("#nbrlamp").val())
            tmpFade = 0;
            tmpDark = 0;
        }
        else {
            tmpFade = $("#fade").val() * 10;
            tmpDark = $("#dark").val() * 10;
        }
        if (dekoder.nbrofsig == 8) {
            alert('Het maximum aantal aan te sluiten seinen is bereikt!');
            return;
        };
        if (dekoder.sigConnected.length == 0) {
            var nextId = 0;
            var nextChannel = 0;
        } else {
            var nextId = dekoder.sigConnected[dekoder.sigConnected.length - 1].sigId + 1
            var nextChannel = dekoder.sigConnected[dekoder.sigConnected.length - 1].sigDraden +
                dekoder.sigConnected[dekoder.sigConnected.length - 1].sigChannel
        };
        if (nextChannel + selSignalType[0].sigDraden > 16) {
            alert('te weinig aansluitingen voor deze keuze op de decoder!');
            return;
        };

        var newSignal = {
            "sigId": nextId,
            "sigType": seinType,
            "sigDraden": selSignalType[0].sigDraden,
            "sigChannel": nextChannel,
            "sigNbrAdr": selSignalType[0].sigNbrAdr,
            "sigAdressen": [parseInt($("#adres1").val())],
            "sigFade": tmpFade,
            "sigDark": tmpDark,
            "sigLamp": [200]
        };

        tmpAdr = $('.adresInput');
        $.each(tmpAdr, function (index, item) {
            if (parseInt($(item).val()) > 0) { newSignal.sigAdressen[index] = parseInt($(item).val()); }
        });

        for (var i = 0; i < selSignalType[0].sigDraden; i++) {
            newSignal.sigLamp[i] = 200;
        };
        console.log(newSignal);
        dekoder.sigConnected.push(newSignal);
        dekoder.nbrofsig++;
        changedValues = true;

        makeHeader();
        makeMainScreen();

    };

    function _cancelKeuzeN() {

        var $el = $('#allTypeSeinen');
        var $sc = $('#signal-config');
        _cleanInput($el, $sc);
        $("#connectedSignal").show();
        $(".Mainbuttoncontainer").show();
        $(".NewButtoncontainer").hide();
        $("#signalNew").hide();
    };

    function _cleanInput($el, $sc) {
        var allRadio = $($el).find('.radio');
        $.each(allRadio, function (index, item) {
            $(item).prop('checked', false);
        });
        var allFade = $($sc).find('#fade');
        $(allFade).val(15);
        $(allFade).next("#sout").html(150);

        var allDark = $($sc).find('#dark');
        $(allDark).val(30);
        $(allDark).next("#sout").html(300);

        var allAdr = $($sc).find('.adresInput');
        $.each(allAdr, function (index, item) {
            $(item).val("");
        });
        var allLampen = $($sc).find('.draadInput');
        $(allLampen).val(1);
    };

    function makeHeader() {
        var data = {
            h1: dekoder.dekName,
            h2: dekoder.sigConnected.length
        };
        console.log(data);
        var $el = $('.header-container');
        if (data.h2 == 0) {
            $($el).html(cleanHeader0);
        } else {
            if (data.h2 == 1) {
                $($el).html(cleanHeader1);
            } else {
                $($el).html(cleanHeader2);
            }
        }
        var template = $el.find('#header-template').html();
        $el.html(Mustache.render(template, data));
    };

    function makeMainScreen() {
        var data = {
            connSignal: [],
        };
        var $el = $('#connectedSignal');

        data.connSignal = dekoder.sigConnected;
        $($el).html(cleanAllConnected);
        template = $el.find('#signal-template').html();
        $el.html(Mustache.render(template, data));
        $("#connectedSignal").show();
        $("#signalNew").hide();
        $(".NewButtoncontainer").hide();
        $("#signal-change").hide();
        $(".ChangeButtoncontainer").hide();
        if (changedValues) {
            $(".storebutton").show();
        } else {
            $(".storebutton").hide();
        };
        $(".Mainbuttoncontainer").show();
    };

    function changeSignal(index) {
        var $el = $('#changeSignal');

        $("#connectedSignal").hide();
        $(".Mainbuttoncontainer").hide();
        $(".ChangeButtoncontainer").show();
        $("#signal-change").show();
        if (index == (dekoder.sigConnected.length - 1)) {
            bdelWasVisibale = true;
            $("#BDel").show();
        } else {
            bdelWasVisibale = false;
            $("#BDel").hide();
        };

        signalToChange = dekoder.sigConnected[index];
        saveOldVal.lamp = dekoder.sigConnected[index].sigLamp;
        saveOldVal.fade = dekoder.sigConnected[index].sigFade;
        saveOldVal.dark = dekoder.sigConnected[index].sigDark;

        var htmlPlaatje = Mustache.render(plaatjeHTML, signalToChange); // build plaatje                
        var htmlChannel = Mustache.render(channelHTML, signalToChange); // Build channel HTML

        // Build Adress HTML
        var htmlAdres = [];
        $.each(signalToChange.sigAdressen, function (index, item) {
            var waardes = {
                item: item,
                index: index + 1,
                adresString: ""
            }
            if (index == 0 && typeof signalToChange.sigAdressen[1] === 'undefined') {
                waardes.adresString = "Adres :";
            } else {
                var i = index + 1;
                waardes.adresString = "Adres " + i + ":";
            }
            htmlAdres[index] = Mustache.render(adresHTML, waardes);
        });

        if (signalToChange.sigType == 'Lamp') {
            $(".fade").hide();
            $(".dark").hide();
        }
        else {
            $(".fade").show();
            $(".dark").show();
            // Build fade HTML
            var fadeWaardes = {
                cSfade10: signalToChange.sigFade / 10,
                cSdark10: signalToChange.sigDark / 10,
                cSfade: signalToChange.sigFade,
                cSdark: signalToChange.sigDark
            }
            var htmlFade = Mustache.render(fadeHTML, fadeWaardes);
        }

        // Build Lamp HTML
        var htmlLamp = [];
        $.each(signalToChange.sigLamp, function (index, item) {
            var waardes = {
                item: item,
                index: index + 1
            }
            htmlLamp[index] = Mustache.render(lampHTML, waardes);
        });
        $($el).html(cleanChangeSignal);
        $el.find('#imageC').append(htmlPlaatje);
        $el.find('#changeForm').append(htmlChannel);
        $el.find('#changeForm').append(htmlAdres);
        $el.find('#changeForm').append(htmlFade);
        $el.find('#changeForm').append(htmlLamp);


    };

    function newSignal() {
        var seinType;
        var data = {
            allVoorseinen: [],
            allHoofdseinen: [],
            allOverig: [],
            allLicht: []
        };
        var $el = $('#allTypeSeinen');
        var $sc = $('#signal-config');
        var template;
        data.allVoorseinen = getObjects(typeSig, 'sigHoofdtype', 'voorsein');
        data.allHoofdseinen = getObjects(typeSig, 'sigHoofdtype', 'hoofdsein');
        data.allOverig = getObjects(typeSig, 'sigHoofdtype', 'overig');
        data.allLicht = getObjects(typeSig, 'sigHoofdtype', 'lamp');
        $($el).html(cleanNewSignal);
        template = $el.find('#seinen-template').html();
        $el.html(Mustache.render(template, data));
        $(".1adres").hide();
        $(".2adres").hide();
        $(".3adres").hide();

        _cleanInput($el, $sc);

        $("#connectedSignal").hide();
        $("#signal-change").hide();
        $(".Mainbuttoncontainer").hide();
        $("#signalNew").show();
        $(".NewButtoncontainer").show();
        $(".instellingen").hide();

    };
});