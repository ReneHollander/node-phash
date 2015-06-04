var pHash = require('./phash.js');

pHash.videoHash(__dirname + "/big_buck_bunny.mp4", function(err, arr) {
  if (err) throw err;
  console.log(arr);
});
