var QsortViz = (function () {

  var qsv = {};
  
  var theArray = [];

  function noOp (){};

  // Static DOM elements
  var vizDiv        = document.getElementById("visualization_div"),
      vizArea       = document.getElementById("visualization_svg"),
      arrayDisplay  = d3.select("#array_display"),
      workDisplay   = d3.select("#work_display"),
      inputField    = document.getElementById("array_input_field"),
      sortButton    = document.getElementById("sort_button"),
      resetButton   = document.getElementById("reset_button");

  // Formatting and styling
  var vizTopOffset       = 25,
      arrAddrTopPadding  = 5,
      arrAddrSidePadding = 1,
      arrDataTopPadding  = 2,
      arrDataSidePadding = 2,
      maxScalingFactor   = 5;
  
  var arrLeftPadding,
      arrElemHeight,
      arrElemWidth,
      scalingFactor;

  var arrayColoringScheme = Object.create(null, {
    addrFillColor   : { enumerable: true, value: "#020a21" },
    addrFillOpacity : { enumerable: true, value: 0.25 },
    dataFillColor   : { enumerable: true, value: "#f7e61c" },
    dataFillOpacity : { enumerable: true, value: 0.5 }
  });

  var workColoringScheme = Object.create(null, {
    addrFillColor        : { enumerable: true, value: "black" },
    addrFillOpacity      : { enumerable: true, value: 0.15 },
    dataFillColor        : { enumerable: true, value: "yellow" },
    dataFillOpacity      : { enumerable: true, value: 0.5 },
    leftCursorFillColor  : { enumerable: true, value: "white" },
    rightCursorFillColor : { enumerable: true, value: "red" }
  });

  var comparisonColors = {
    "<": "aqua",
    ">": "red"
  }
 
  var transitionDuration = 100;
  
  function computeTopOffsetForDepth(depth) {
    if (scalingFactor === undefined) setLayoutValues();

    return vizTopOffset + ((arrElemHeight + arrAddrTopPadding) * depth);
  }

  function ensurePageHoldsVizualization(topOffset) {
    if ((topOffset + arrElemHeight + arrAddrTopPadding) > +vizArea.style.height.slice(0,-2)) {
      vizArea.style.height = vizDiv.style.height = (topOffset + arrElemHeight + arrAddrTopPadding) + "px";
    }
  }

  var setLayoutValues = (function() {

    function getDataTextHeight() {
      return arrayVizualization.arrData.node().getBBox().height;
    };

    function getMaxDataTextWidth() {
      var maxWidth  = 0,
          temp;

      if(arrayVizualization.arrData) arrayVizualization.arrData.each(function() { 
        if ((temp = this.getBBox().width) > maxWidth) { maxWidth = temp; }
      });
      return maxWidth;
    };

    function setVizScalingFactorAndPadding(arrElemWidth) {
      var unscaledWidth = (arrElemWidth + 2*arrAddrSidePadding) * theArray.length,
          vizAreaWidth  = vizArea.offsetWidth || vizDiv.offsetWidth;

      scalingFactor = (vizAreaWidth / unscaledWidth < 5) ? vizAreaWidth / unscaledWidth : 5;

      arrLeftPadding = (scalingFactor > 1) ? ( vizAreaWidth - (unscaledWidth * scalingFactor)) /2 : 0;
    };

    function setArrayVizHeight(textHeight) {
      arrElemHeight = (textHeight + arrAddrTopPadding)*scalingFactor;
    }

    function setArrayVizWidth(maxTextWidth) {
      arrElemWidth = (maxTextWidth + arrAddrSidePadding)*scalingFactor;
    }

    return function() {
      var maxElemHeight,
          maxElemWidth;

      if (!arrayVizualization.arrData) resetLayoutValues();
      else {
        maxElemHeight = getDataTextHeight();
        maxElemWidth  = getMaxDataTextWidth();
        
        setVizScalingFactorAndPadding(maxElemWidth);
        setArrayVizHeight(maxElemHeight);
        setArrayVizWidth(maxElemWidth);
      }
    };
  })(); 


  function resetLayoutValues() {
    arrLeftPadding = undefined;
    arrElemHeight  = undefined;
    arrElemWidth   = undefined;
    scalingFactor  = undefined;
  };



  var arrayVizPrototype = (function() {

    var that = {};

    function initElems(hoc) {

      hoc.arrElems = hoc.displayArea.selectAll("g")
                                  .data(theArray.slice(hoc.p, hoc.q))
                                  .enter()
                                  .append("g");

      hoc.arrAddrs = hoc.arrElems.append("rect")
                                   .attr("class", function(d,i) { return "arrAddr_" + (i + hoc.p); })
                                   .style("fill", hoc.addrFillColor)
                                   .style("fill-opacity", hoc.addrFillOpacity);
      hoc.arrData  = hoc.arrElems.append("text")
                                   .attr("class", function(d,i) { return "arrData_" + (i + hoc.p); })
                                   .style("fill", hoc.dataFillColor)
                                   .style("fill-opacity", hoc.dataFillOpacity)
                                   .style("text-anchor", "middle")
                                   .text(function(d) { return d; });
    };


    that.render = function (callBack) {

      var hoc = this;

      initElems(this);

      this.topOffset = computeTopOffsetForDepth(this.depth);

      this.getLeftOffset = function (i) {
        return arrLeftPadding + (arrElemWidth + arrAddrSidePadding)*(i + this.p);
      }

      this.arrAddrs.attr("height", arrElemHeight)
                   .attr("width", arrElemWidth);
      this.arrData.attr("transform", "scale("+ scalingFactor +")")
                  .attr("x", (arrElemWidth/2)/scalingFactor)
                  .attr("dy", (3*arrElemHeight/4)/scalingFactor);

      ensurePageHoldsVizualization(this.topOffset);

      this.arrElems.attr("transform", function(d,i) { 
                                        return "translate( " + hoc.getLeftOffset(i)  + ", " + computeTopOffsetForDepth(hoc.depth -1) + " )"; })
                   .transition()
                   .duration(transitionDuration*10)
                   .attr("transform",  function(d,i) { 
                                        return "translate( " + hoc.getLeftOffset(i)  + ", " + computeTopOffsetForDepth(hoc.depth) + " )"; })
                   .each("end", function (d,i) { if (i === (hoc.arrElems[0].length - 1)) callBack() });
    };

    that.finalizeElem = function (elem, callBack) { 
      d3.select(this.arrAddrs[0][elem - this.p]).style("fill-opacity", 1);
      d3.select(this.arrData[0][elem - this.p]).style("fill-opacity", 1);
      callBack();
    }     

    return that;
  })(); // End arrayVizPrototype



  var cursor_prototype = (function () {
    var that = Object.create(null); 

    that.getCurrentLeftOffset = function() {
      return this.hostArray.getLeftOffset(this.hostArray[this.side + "CursorPos"] - this.hostArray.p);
    }

    function init (hoc) {

      hoc.displayArea = hoc.hostArray.displayArea.append("g")
                                                 .attr("class", hoc.side + "Cursor");

      hoc.displayArea.append("rect")
                     .attr("height", arrElemHeight)
                     .attr("width", arrElemWidth)
                     .style("fill", "black")
                     .style("fill-opacity", 0)
                     .style("stroke-width", arrDataSidePadding/2)
                     .style("stroke", workColoringScheme[hoc.side + "CursorFillColor"])
                     .style("stroke-opacity", 1);
    }

    that.render = function (callBack) {
      var hoc = this;

      init(this);
      this.displayArea.attr("transform", "translate( " + hoc.getCurrentLeftOffset() + ", " + hoc.hostArray.topOffset + " )");

      callBack && callBack();
    }

    that.removeSelf = function (callBack) {
      var hoc = this;

      function bye() {
        this.remove();
        //hoc.displayArea.select("." + this.side + "Cursor").remove(); 
        callBack && callBack();
      }

      this.displayArea.transition()
                     .duration(transitionDuration)
                     .style("stroke-opacity", 0)
                     .each("end", bye);
    }

    that.updatePosition = function (callBack) {
      var hoc = this;

      if ((this.side === "left") && (this.hostArray.leftCursorPos === this.hostArray.q)) {
        this.removeSelf(callBack);
      } else {
        this.displayArea.transition()
                       .duration(transitionDuration/1.618)
                       .attr("transform", "translate( " + hoc.getCurrentLeftOffset() + ", " + hoc.hostArray.topOffset + " )")
                       .each("end", callBack); 
      }
    }

    return that;
  })(); 


  var arrayVizualization = (function() {
    
    var that = Object.create(arrayVizPrototype),
        key;

    function resetElems() { that.arrElems = that.arrAddrs = that.arrData  = null; };

    for (key in arrayColoringScheme) that[key] = arrayColoringScheme[key];

    that.displayArea = arrayDisplay;

    that.depth = 0;
    that.p = 0;
    that.q = theArray.length;

    that.reset = function() { 
      resetElems(); 
      that.q = theArray.length;
    };

    that.refresh = function() {
      that.reset();
      that.render(noOp);
    };

    return that;
  })(); // End arrayVizualization


  var newWorkVizPrototype = (function() {

    var that = Object.create(arrayVizPrototype);

    that.makeSVGNode = function () {
      this.displayArea = d3.select(document.createElementNS("http://www.w3.org/2000/svg", "g"));
      workDisplay.node().appendChild(this.displayArea.node());
    }

     that.showComparison = function (x, y, compOp, callBack) {

      if (x !== y) { 

        var elems     = d3.selectAll([ this.arrAddrs[0][x - this.p], this.arrAddrs[0][y - this.p] ]);
        var pColor    = elems[0][0].style.fill;
        var qColor    = elems[0][1].style.fill;
        var compColor = (compOp) ? comparisonColors[compOp.trim().charAt(0)] : "pink";

         elems.transition()
              .style("fill", compColor)
              .transition()
              .duration(transitionDuration)
              .style("fill", function(d,i) { return (i) ? qColor : pColor; })
              .each("end", function(d, i) { if(i === (elems.length - 1)) callBack(); }); 
       }
       else callBack();
     };


     that.swap = function (x,y, callBack) { 

       var hoc = this,
           origColor,
           origOpacity,
           elems,
           temp;

       if (x !== y) { 

         elems = [ this.arrData[0][x - this.p], 
                   this.arrData[0][y - this.p],
                   arrayVizualization.arrData[0][x],
                   arrayVizualization.arrData[0][y]
                 ];
             
         origColor   = elems.map(function(e) { return e.style.fill || "black" });
         origOpacity = elems.map(function(e) { return e.style["fill-opacity"] || 1 });

         d3.selectAll(elems)
           .transition()
           .style("fill", "white")
           .style("fill-opacity", 1)
           .transition()
           .duration(transitionDuration)
           .style("fill", function(d,i) { return origColor[i]; })
           .style("fill-opacity", function(d,i) { return origOpacity[i]; })
           .text(function(d, i) { return (i%2) ? theArray[y] : theArray[x]; })
           .each("end", function(d,i) { if(i === (elems.length - 1)) callBack(); });
       }
       else callBack();
     };

     that.newLeftCursor = function() {
       var that  = Object.create(cursor_prototype);

       that.hostArray = this;
       that.side = "left";

       return that;
     } 

     that.newRightCursor = function() {
       var that  = Object.create(cursor_prototype);

       that.hostArray = this;
       that.side = "right";

       return that;
     } 

    that.addCursors = function (callBack) {
      this.leftCursor  = this.newLeftCursor();
      this.rightCursor = this.newRightCursor();

      this.leftCursor.render(noOp);
      this.rightCursor.render(callBack);
    }

    that.updateLeftCursor = function (callBack) {
      this.leftCursor.updatePosition(callBack);      
    }

    that.updateRightCursor = function (callBack) {
      this.rightCursor.updatePosition(callBack);
    }

    that.finalize = function (elem, callBack) {
      this.arrElems.select(".arrAddr_" + elem)
                   .style("fill", arrayColoringScheme.addrFillColor)
                   .style("fill-opacity", (arrayColoringScheme.addrFillOpacity)*1.618);
      this.arrElems.select(".arrData_" + elem)
                   .style("fill", arrayColoringScheme.dataFillColor)
                   .style("fill-opacity", (arrayColoringScheme.dataFillOpacity)*1.618);
      this.leftCursor  && this.leftCursor.removeSelf(noOp);
      this.rightCursor && this.rightCursor.displayArea.select("rect")
                                          .style("stroke", arrayColoringScheme.dataFillColor)
                                          .style("stroke-opacity", 1);
      arrayVizualization.finalizeElem(elem, callBack);
    }

    that.finishPartitioning = function(callBack) {  
      var hoc = this;

      this.swap(this.p, this.rightCursorPos, function() { 
        hoc.finalize(hoc.rightCursorPos, callBack); 
      });
     };

     that.indicateBaseCase = function(callBack) { 
       var hoc = this;

       this.render(function() { 
         hoc.finalize(hoc.p, callBack); 
       }) 
     };

     that.compareLeftCursorToPivot  = function(compOp, callBack) { this.showComparison(this.p, this.leftCursorPos, compOp, callBack); };
     that.compareRightCursorToPivot = function(compOp, callBack) { this.showComparison(this.p, this.rightCursorPos, compOp, callBack); };
     that.incrementLeftCursor       = function(callBack) { ++this.leftCursorPos;  
                                                           this.updateLeftCursor(callBack); };
     that.decrementRightCursor      = function(callBack) { --this.rightCursorPos; 
                                                           this.updateRightCursor(callBack); };

     return that;
 })();


 var newWorkVisualization = (function() {

    return function (p, q, leftCursorPos, rightCursorPos, depth) {
      var that = Object.create(newWorkVizPrototype);

      that.p              = p;
      that.q              = q;
      that.depth          = depth;
      that.leftCursorPos  = leftCursorPos;
      that.rightCursorPos = rightCursorPos;

      for (key in workColoringScheme) that[key] = workColoringScheme[key];

      that.makeSVGNode();

      return that;
    }
  })();


  var sorterCallback = (function() {

    var currentWorkViz;

    return function () {

      var args = arguments;

      function callBack() {
        setTimeout(args[args.length - 1], 0);
        //args[args.length - 1]();
      }

      switch (arguments[0]) {
        case "enter_function":
          currentWorkViz = newWorkVisualization(args[1], args[2], args[3], args[4], args[5]);
          currentWorkViz.render(function() { currentWorkViz.addCursors(callBack); });
          break;
        case "base_case":
          currentWorkViz = newWorkVisualization(args[1], args[2], args[3], args[4], args[5]);
          currentWorkViz.indicateBaseCase(callBack);
          break;
        case "compare_left_cursor_to_pivot":
          currentWorkViz.compareLeftCursorToPivot(args[1], callBack);
          break;
        case "increment_left_cursor":
          currentWorkViz.incrementLeftCursor(callBack);
          break;
        case "compare_right_cursor_to_pivot":
          currentWorkViz.compareRightCursorToPivot(args[1], callBack);
          break;
        case "decrement_right_cursor":
          currentWorkViz.decrementRightCursor(callBack);
          break;
        case "swap":
          currentWorkViz.swap(args[1], args[2], callBack);
          break;
        case "finish_partitioning":
          currentWorkViz.finishPartitioning(callBack);
          break;
        default: 
          console.warn("Unsupported sorter vizualization callback.");
          callBack();
      }
    }
  })(); 


  function reset() {
    theArray.length = 0;
    resetLayoutValues();

    arrayDisplay.selectAll("*").remove();  
    arrayVizualization.reset();

    workDisplay.selectAll("*").remove();  
  };

  function updateArray() {
    reset();
    theArray = inputField.value.trim().split(/[ ,]+/);

    if (theArray[0] === "") return;
    else for (var i = 0; i < theArray.length; ++i)  { theArray[i] = +theArray[i]; }   // Strings to Numbers.

    arrayVizualization.refresh();
  }

  qsv.reset = reset;

  qsv.modifyArray = function() {
    if (event.keyCode != 13) return;
    else updateArray();
  }

  qsv.sortArray = function() {
    sortButton.disabled = true;
    resetButton.disabled = true;
    updateArray();
    Quicksorter.sort(theArray, false, false,  sorterCallback, function() { 
                                                                sortButton.disabled = false; 
                                                                resetButton.disabled = false;});
  }

  return qsv;
})();
