var Quicksorter =  Object.create(null);

Quicksorter.sort = function(theArray, randomize, threaded, visualizer, onHALT) {

  if (!visualizer) visualizer = function(){ setTimeout(arguments[arguments.length-1], 1); };
  if (!onHALT) onHALT = function noOp() {};

  function trampoline(fn) { 
    while (fn = fn());
  };

  function swapValuesAt(i, j) {
    var temp = theArray[i];
    theArray[i] = theArray[j];
    theArray[j] = temp;
  }

  function randomizeThePivot(p, q, recursiveDepth, callBack) {
    var args = arguments,
        rand;

    rand = Math.floor(Math.random()*(q-p)) + p;
    swapValuesAt(p, rand);
    visualizer("swap", p, rand, function () { 
      trampoline.call(null, function () { return advanceLeftCursor.apply(null, args); });
    });
  }

  function advanceLeftCursor(p, q, recursiveDepth, callBack, leftCursor, rightCursor) {
    if (leftCursor === undefined) leftCursor = p+1;

    function incrementLeftCursor() {
      if (theArray[leftCursor] <= theArray[p]) {
        ++leftCursor;
        visualizer("increment_left_cursor", function () {
          trampoline.call(null, function () { 
            return compareLeftCursorToPivot.apply(null, [p, q, recursiveDepth, callBack, leftCursor, rightCursor]) });
        });
      } else return function () { 
        return advanceRightCursor.apply(null, [p, q, recursiveDepth, callBack, leftCursor, rightCursor])
      };
    }

    function compareLeftCursorToPivot() {
      if (leftCursor < q) {
        visualizer("compare_left_cursor_to_pivot", "<", function () {
          trampoline.call(null, function () { 
            return incrementLeftCursor.apply(null, [p, q, recursiveDepth, callBack, leftCursor, rightCursor]); } ); 
        });
      } else {
        return function () { 
                  return advanceRightCursor.apply(null, [p, q, recursiveDepth, callBack, leftCursor, rightCursor]);
               };
      }
    } 

    compareLeftCursorToPivot();
  }

  function advanceRightCursor(p, q, recursiveDepth, callBack, leftCursor, rightCursor) {
    if (rightCursor === undefined) rightCursor = q-1;

    function decrementRightCursor() {
      if (theArray[rightCursor] >= theArray[p] && rightCursor >= leftCursor) {
        --rightCursor;
        visualizer("decrement_right_cursor", function () {
          trampoline.call(null, function() { 
            return compareRightCursorToPivot.apply(null, [p, q, recursiveDepth, callBack, leftCursor, rightCursor]);
          }); 
        });
      } else return function () { 
          return swapValuesAtCursors.apply(null, [p, q, recursiveDepth, callBack, leftCursor, rightCursor]);
      };
    }

    function compareRightCursorToPivot() {
      if (rightCursor > p) {
        visualizer("compare_right_cursor_to_pivot", ">", function() {
          trampoline.call(null, function () { 
            return decrementRightCursor.apply(null, [p, q, recursiveDepth, callBack, leftCursor, rightCursor]);
          }); 
        });
      } else return function() { 
        return swapValuesAtCursors.apply(null, [p, q, recursiveDepth, callBack, leftCursor, rightCursor]); 
      };
    }

    compareRightCursorToPivot();
  }

  function swapValuesAtCursors(p, q, recursiveDepth, callBack, leftCursor, rightCursor) {
    var args = arguments;

    if (leftCursor < rightCursor) {
      swapValuesAt(leftCursor, rightCursor);
      visualizer("swap", leftCursor, rightCursor, function () {
        trampoline.call(null, function () { return advanceLeftCursor.apply(null, args); } );
      });
    } 
    else return function () { return finishPartitioning.apply(null, args); };
  }

  function finishPartitioning(p, q, recursiveDepth, callBack, leftCursor, rightCursor) {
    var args = arguments;

    swapValuesAt(p, rightCursor);
    //visualizer("swap", p, rightCursor, function() {
      //trampoline.call(null, function() {
        visualizer("finish_partitioning", function () {
          trampoline.call(null, function () { return recurseLeft.apply(null, args); });
        });
      //});
    //});
  }

  function recurseLeft(p, q, recursiveDepth, callBack, leftCursor, rightCursor) {
    var args = arguments;

    if (rightCursor > p) {
      return function () { return doSort.apply(null, [p, rightCursor, (recursiveDepth + 1), function() {
        return recurseRight.apply(null, args);
      }]); };
    }
    else return function () { return recurseRight.apply(null, args); } 
  }

  function recurseRight(p, q, recursiveDepth, callBack, leftCursor, rightCursor) {
    if ((q-rightCursor) > 1) {
      return function () { 
        return doSort.apply(null, [(rightCursor+1), q, (recursiveDepth + 1), function () {
          return function () { return callBack(); };
        }]); 
      };
    } else return function() { return callBack(); };
  }

  function doSort (p, q, recursiveDepth, callBack) {
    var args = arguments;

    if ((q-p) === 1) { 
      visualizer("base_case", p, q, p+1, q-1, recursiveDepth, function () { //FIXME
        trampoline.call(null, function () { return callBack(); });
      });
    } 
    else {
      visualizer("enter_function", p, q, p+1, q-1, recursiveDepth, function() { 
        var next = (randomize) ? randomizeThePivot : advanceLeftCursor;

        trampoline.call(null, function () { return function () { return next.apply(null, args); }; });
        //trampoline.call(null, function () { return next.apply(null, args); });
      });
    }
  }

  // START
  trampoline(function () { return doSort(0, theArray.length, 1, onHALT); });
}
