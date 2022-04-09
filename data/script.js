$(function() {


    $(".signal-types").hide();

    // Get base dekoder data
    getDatafromServer();
    //////////// Build main screen
    makeHeader();
    makeMainScreen();
    setEvents();


    var typeSig;
    var saveOldVal = {
        fade: null,
        dark: null,
        lamp: []
    };
    var changedValues = false;
    var signalToChange;

    function getDatafromServer() {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
                deKoder = this.responseText;
                console.log(deKoder);
                dekoder = JSON.parse(deKoder);
                console.log(dekoder);
                typeSig = JSON.parse(typeSignalen);
                headers.makeHeader();
                mainScreen.makeMain();
            }
        };
        console.log('getDataFromServer');
        xhttp.open("GET", "/GetDecVal", true);
        xhttp.send();
        console.log('request for data sent');
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
        $('.main-container').delegate('#BNew', 'click', newSignal);
        $('.main-container').delegate('#BStore', 'click', _storeValues);
        $('#connectedSignal').delegate('.sigBut', 'click', _changeSig);
        $('#changeSignal').delegate('input.slider', 'input', showSliderVal);
        $('.footercontainer').delegate('#BCancelC', 'click', _cancelKeuzeC);
        $('.footercontainer').delegate('#BDel', 'click', _deleteSignal);
        $('.footercontainer').delegate('#BApply', 'click', _processValues);
        $('.footercontainer').delegate('#BTest', 'click', _testLights);
        $('.footercontainer').delegate('#BTestEnd', 'click', _endTestLights);

        $('#allTypes').delegate('input:radio[name=sigGekozen]', 'click', _showAdresInput);
        $('#signal-config').delegate('input.slider', 'input', showSliderVal);
        $('#allTypes').delegate('#BKeuze', 'click', _processKeuze);
        $('#allTypes').delegate('#BCancelN', 'click', _cancelKeuzeN.bind(this));
    };

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
        console.log(dekoder);
        const jsonDekoder = JSON.stringify(dekoder);
        console.log(jsonDekoder);

        // open request
        xhr.open("POST", "/PostDecVal");

        // set `Content-Type` header
        xhr.setRequestHeader('Content-Type', 'application/json');

        // send rquest with JSON payload
        xhr.send(JSON.stringify(jsonDekoder));

    };

    function _changeSig() {
        changeSignal($(this).attr('id'));
    };

    function _cancelKeuzeC() {
        dekoder.sigConnected[signalToChange.sigId].sigLamp = saveOldVal.lamp;
        dekoder.sigConnected[signalToChange.sigId].sigFade = saveOldVal.fade;
        dekoder.sigConnected[signalToChange.sigId].sigDark = saveOldVal.dark;
        console.log(dekoder.sigConnected[signalToChange.sigId]);
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

    function _processValues() {
        var i = signalToChange.sigId;

        dekoder.sigConnected[i].sigFade = $("#fade").val() * 10;
        dekoder.sigConnected[i].sigDark = $("#dark").val() * 10;

        var tmpLamp = $('.lampInput');
        $.each(tmpLamp, function(count, item) {
            dekoder.sigConnected[i].sigLamp[count] = $(item).val();
        });
        changedValues = true;
        makeHeader();
        makeMainScreen();
    };

    function _endTestLights() {
        //call server met waardes van alle lampen
        $("#BApply").show();
        $("#BDel").show();
        $("#BCancel").show();
        $(".testbutTE").hide();
    };

    function _testLights() {
        //call server met waardes van alle lampen
        $("#BApply").hide();
        $("#BDel").hide();
        $("#BCancel").hide();
        $(".testbutTE").show();
    };

    function showSliderVal() {
        return $(this).each(function() {
            if ($(this).attr("id") == "fade" || $(this).attr("id") == "dark") {
                var value = $(this).val() * 10;
            } else {
                var value = $(this).val()
            };
            $(this).next("#sout").html(value);

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
        $(".instellingen").show();
    };

    function _processKeuze() {
        var selSignalType = getObjects(typeSig, 'sigType', seinType);
        if (dekoder.sigConnected.length == 0) {
            var nextId = 0;
            var nextChannel = 0;
        } else {
            var nextId = dekoder.sigConnected[dekoder.sigConnected.length - 1].sigId + 1
            var nextChannel = dekoder.sigConnected[dekoder.sigConnected.length - 1].sigDraden +
                dekoder.sigConnected[dekoder.sigConnected.length - 1].sigChannel
        };
        if (nextChannel + selSignalType[0].sigDraden > 16) {
            alert('te weinig aansluitingen voor dit sein op de decoder!');
            return;
        }
        var newSignal = {
            "sigId": nextId,
            "sigType": seinType,
            "sigDraden": selSignalType[0].sigDraden,
            "sigChannel": nextChannel,
            "sigNbrAdr": selSignalType[0].sigNbrAdr,
            "sigAdressen": [parseInt($("#adres1").val())],
            "sigImage": selSignalType[0].sigImage,
            "sigFade": $("#fade").val() * 10,
            "sigDark": $("#dark").val() * 10,
            "sigLamp": [200]
        };

        tmpAdr = $('.adresInput');
        $.each(tmpAdr, function(index, item) {
            if (parseInt($(item).val()) > 0) { newSignal.sigAdressen[index] = parseInt($(item).val()); }
        });

        for (var i = 0; i < newSignal.sigDraden; i++) {
            newSignal.sigLamp[i] = 200;
        };
        dekoder.sigConnected.push(newSignal);
        changedValues = true;

        makeHeader();
        makeMainScreen();

    };

    function _cancelKeuzeN() {

        var $el = $('#allTypes');
        var $sc = $('#signal-config');
        _cleanInput($el, $sc);
        $(".signal-set").show();
        $(".NBcontainer").show();
        $(".signal-types").hide();
    };

    function _cleanInput($el, $sc) {
        var allRadio = $($el).find('.radio');
        $.each(allRadio, function(index, item) {
            $(item).prop('checked', false);
        });
        var allFade = $($sc).find('#fade');
        $(allFade).val(15);
        $(allFade).next("#sout").html(150);

        var allDark = $($sc).find('#dark');
        $(allDark).val(30);
        $(allDark).next("#sout").html(300);

        var allAdr = $($sc).find('.adresInput');
        $.each(allAdr, function(index, item) {
            $(item).val("");
        });
    };

    function makeHeader() {
        var data = {
            h1: dekoder.dekName,
            h2: dekoder.sigConnected.length
        };
        var $el = $('.header-container');
        console.log('make header');
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
        console.log(data);
        $el.html(Mustache.render(template, data));
    };

    function makeMainScreen() {
        var data = {
            connSignal: [],
        };
        var $el = $('#connectedSignal');
        var $al = $('.main-container');

        data.connSignal = dekoder.sigConnected;
        $($el).html(cleanAllConnected);
        template = $el.find('#signal-template').html();
        $el.html(Mustache.render(template, data));
        $(".signal-set").show();
        $(".signal-types").hide();
        $(".signal-mutate").hide();
        if (changedValues) {
            $(".storebutton").show();
        } else {
            $(".storebutton").hide();
        };
        $(".NBcontainer").show();
        $(".signal-mutate").hide();
    };

    function changeSignal(index) {
        var $el;
        var $el = $('#changeSignal');

        $(".signal-set").hide();
        $(".NBcontainer").hide();
        $(".signal-mutate").show();
        if (index == (dekoder.sigConnected.length - 1)) {
            $("#BDel").show();
        } else {
            $("#BDel").hide();
        };
        $(".testbutTE").hide();

        signalToChange = dekoder.sigConnected[index];
        console.log(dekoder);
        console.log(signalToChange);
        saveOldVal.lamp = dekoder.sigConnected[index].sigLamp;
        saveOldVal.fade = dekoder.sigConnected[index].sigFade;
        saveOldVal.dark = dekoder.sigConnected[index].sigDark;

        var htmlPlaatje = Mustache.render(plaatjeHTML, signalToChange); // build plaatje                
        var htmlChannel = Mustache.render(channelHTML, signalToChange); // Build channel HTML

        // Build Adress HTML
        var htmlAdres = [];
        $.each(signalToChange.sigAdressen, function(index, item) {
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

        // Build fade HTML
        var fadeWaardes = {
            cSfade10: signalToChange.sigFade / 10,
            cSdark10: signalToChange.sigDark / 10,
            cSfade: signalToChange.sigFade,
            cSdark: signalToChange.sigDark
        }
        var htmlFade = Mustache.render(fadeHTML, fadeWaardes);

        // Build Lamp HTML
        var htmlLamp = [];
        $.each(signalToChange.sigLamp, function(index, item) {
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
            allOverig: []
        };
        var $el = $('#allTypes');
        var $sc = $('#signal-config');
        var template;
        data.allVoorseinen = getObjects(typeSig, 'sigHoofdtype', 'voorsein');
        data.allHoofdseinen = getObjects(typeSig, 'sigHoofdtype', 'hoofdsein');
        data.allOverig = getObjects(typeSig, 'sigHoofdtype', 'overig');
        $($el).html(cleanNewSignal);
        template = $el.find('#seinen-template').html();
        $el.html(Mustache.render(template, data));
        $(".1adres").hide();
        $(".2adres").hide();
        $(".3adres").hide();

        _cleanInput($el, $sc);

        $(".signal-set").hide();
        $(".NBcontainer").hide();
        $(".instellingen").hide();
        $(".signal-types").show();

    };


});