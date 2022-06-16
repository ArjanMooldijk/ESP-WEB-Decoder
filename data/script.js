$(function() {


    // $(".signal-types").hide();

    // Get base dekoder data
    getDatafromServer();


    var typeSig;
    var saveOldVal = {
        fade: null,
        dark: null,
        lamp: []
    };
    var changedValues = false;
    var bdelWasVisibale;
    var signalToChange;
    var dekoder;
    var deKoder;
    var typeSig

    function getDatafromServer() {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
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
            } else if (this.status > 200){
                console.log('get from server failed');
                console.log(this.status);
            }
        };
        xhttp.open("GET", "/GetDecVal", true);
        xhttp.send();
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
        $('.ChangeButtoncontainer').delegate('#BCancelC', 'click', _cancelKeuzeC);
        $('.ChangeButtoncontainer').delegate('#BDel', 'click', _deleteSignal);
        $('.ChangeButtoncontainer').delegate('#BApply', 'click', _processChange.bind(this));
        $('.ChangeButtoncontainer').delegate('#BTest', 'click', _testLights.bind(this));
        $('.ChangeButtoncontainer').delegate('#BTestEnd', 'click', _endTestLights);

        $('#allTypeSeinen').delegate('input:radio[name=sigGekozen]', 'click', _showAdresInput);
        $('#signal-config').delegate('input.slider', 'input', showSliderVal);
        $('.NewButtoncontainer').delegate('#BKeuze', 'click', _processKeuze);
        $('.NewButtoncontainer').delegate('#BCancelN', 'click', _cancelKeuzeN);
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
        if (bdelWasVisibale) {
            $("#BDel").show();
        };
        $("#BCancel").show();
        $(".testbutTE").hide();
        console.log("sending end test")
        var subject = {
            sigId : signalToChange.sigId
        };
        const xhttp = new XMLHttpRequest();

        // listen for `load` event
        xhttp.onload = () => {
            // print JSON response
            if (xhttp.status >= 200 && xhttp.status < 300) {
                console.log(xhttp.responseText);
            } else {
                alert(xhttp.responseText);
            }
        };

        // create a JSON object
        const jsonSubject = JSON.stringify(subject);
        console.log(jsonSubject);

        // open request
        xhttp.open("POST", "/EndTest");

        // set `Content-Type` header
        xhttp.setRequestHeader('Content-Type', 'application/json');

        // send rquest with JSON payload
        xhttp.send(jsonSubject);    

/*         var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
                console.log(this.responseText);
            } 
        };
        xhttp.open("GET", "/EndTest", true);
        xhttp.send(); */
    };

    function _testLights() {
        //call server met waardes van alle lampen
        $("#BApply").hide();
        if($("#BDel").is(":visible")){
            bdelWasVisibale = true;
            $("#BDel").hide();
        } else{            
            bdelWasVisibale = false;
        };
        $("#BCancel").hide();
        $(".testbutTE").show();
        // verzamel de waarden

        var $el = ('#changeForm');

        var subject = {
            sigId : signalToChange.sigId,
            sigFade: 0,
            sigDark: 0,
            sigLamp: []
        };
        // dekoder.sigConnected[i].sigFade = $(this).find('#fade').next('.sout').html() * 10;
        // dekoder.sigConnected[i].sigDark = $(this).find('#dark').next('.sout').html() * 10;
        subject.sigFade = $($el).find('#fade').next('.sout').html();
        subject.sigDark = $($el).find('#dark').next('.sout').html();

        var tmpLamp = $('.lampInput');
        $.each(tmpLamp, function(count, item) {
            subject.sigLamp[count] = $(item).val();
        });

        const xhr = new XMLHttpRequest();

        // listen for `load` event
        xhr.onload = () => {
            // print JSON response
            if (xhr.status >= 200 && xhr.status < 300) {
                // parse JSON
                // const response = JSON.parse(xhr.responseText);
                console.log(xhr.responseText);
            } else {
                alert(xhr.responseText);
            }
        };

        // create a JSON object
        const jsonSubject = JSON.stringify(subject);
        console.log(jsonSubject);

        // open request
        xhr.open("POST", "/testLights");

        // set `Content-Type` header
        xhr.setRequestHeader('Content-Type', 'application/json');

        // send rquest with JSON payload
        xhr.send(jsonSubject);    
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
            alert('te weinig aansluitingen voor dit sein op de decoder!');
            return;
        };
        var newSignal = {
            "sigId": nextId,
            "sigType": seinType,
            "sigDraden": selSignalType[0].sigDraden,
            "sigChannel": nextChannel,
            "sigNbrAdr": selSignalType[0].sigNbrAdr,
            "sigAdressen": [parseInt($("#adres1").val())],
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
        $(".testbutTE").hide();

        signalToChange = dekoder.sigConnected[index];
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
        var $el = $('#allTypeSeinen');
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

        $("#connectedSignal").hide();
        $("#signal-change").hide();
        $(".Mainbuttoncontainer").hide();
        $("#signalNew").show();
        $(".NewButtoncontainer").show();

    };
});