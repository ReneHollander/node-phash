var assert = require("assert");
var pHash = require('../lib/phash');
require("should");

var examples = [{
  path: __dirname + "/data/a.jpg",
  hash: "2816561582497829945"
}, {
  path: __dirname + "/data/a.jpg",
  hash: "2816561582497829945"
}, {
  path: __dirname + "/data/c.png",
  hash: "15433968795834791622"
}, {
  path: __dirname + "/data/d.jpg",
  hash: "12040987020241900649"
}];

describe("pHash", function() {
  describe("async test", function() {
    var test = examples[0];
    examples.forEach(function(i) {
      it(i.path, function(done) {
        pHash.imageHash(i.path, function(err, lower, higher) {
          if (err) {
            done(err);
          }
          console.log("lower bits: " + lower + ", higher bits: " + higher);
          done();
        });
      });
    });

    it("should fail", function(done) {
      pHash.imageHash(__dirname + "/data/h.png", function(err, lower, higher) {
        console.log(err);
        console.log("lower bits: " + lower + ", higher bits: " + higher);
        assert(err);
        done();
      });
    });
  });
});
