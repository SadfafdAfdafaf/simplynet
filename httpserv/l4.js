const queue_graph_max = 19;
const queue_graph_sprite_cnt = 8;
const animation_interval = 20;

var queue_a;
var queue_b;
var proc_l;
var proc_s;

var q_len;
var r_cnt;
var flag_cycle;
var ret_prob;

var mmode;
var mdt;

var sim_button;
var result;
var sim_info;
var queue_graph;

var sdata_a;
var sdata_b;
var sdata_c;
var sdata_d;
var sdata_e;
var sdata_f;

var editable_objs;

var sim_active = false;
var animation_stopped;
var animation_interval_id;

function rand_uniform(a, b) {
  return ((Math.random() * (b - a)) | 0) + a;
}

function rand_poisson(mu, sigma) {
  var p = Math.random();
  var pm = Math.exp(-((p-mu)*(p-mu))/(2*sigma*sigma));
  var ass = 1/(sigma*Math.sqrt(2*Math.pi));
  var k = ass*pm;
  

  return k;
}

function init() {
  queue_a = document.getElementById("queue-a");
  queue_b = document.getElementById("queue-b");
  proc_l = document.getElementById("processor-mu");
  proc_s = document.getElementById("processor-sigma");
  
  q_len = document.getElementById("queue-length");
  r_cnt = document.getElementById("req-count");
  ret_prob = document.getElementById("return-prob");
  
  mmode = document.getElementById("mode");
  mdt = document.getElementById("dt");
  
  sim_button = document.getElementById("sim-button");
  result = document.getElementById("result");
  sim_info = document.getElementById("simulation-info");
  queue_graph = document.getElementById("queue-graph");
  
  sdata_a = document.getElementById("sdata-a");
  sdata_b = document.getElementById("sdata-b");
  sdata_c = document.getElementById("sdata-c");
  sdata_d = document.getElementById("sdata-d");
  sdata_e = document.getElementById("sdata-e");
  sdata_f = document.getElementById("sdata-f");
  
  editable_objs = [queue_a, queue_b, proc_l, proc_s, q_len, r_cnt, ret_prob, mmode, mdt];

}

function get_time_generator() {
  return rand_uniform(Number(queue_a.value), Number(queue_b.value));
}

function get_time_processor() {
  return rand_poisson(Number(proc_l.value), Number(proc_s.value));
}

function update_sim_data(queue, left, processed, lost, returned) {
  var len = queue.length;
  sdata_b.innerHTML = len;
  sdata_c.innerHTML = left;
  sdata_d.innerHTML = processed;
  sdata_e.innerHTML = returned;
  sdata_f.innerHTML = lost;
}

function queue_add_req(queue, qlen) {
  if (queue.length == qlen)
    return false;
  
  queue[queue.length] = Math.floor(Math.random() * queue_graph_sprite_cnt);
  return true;
}

function start_simulation(gen_time_f, proc_time_f) {
 
  var qlen = Number(q_len.value) | 0;
  var rcnt = Number(r_cnt.value) | 0;
  var retprob = Number(ret_prob.value) * 0.01;
  var queue = [];
  
  var lost = 0;
  var processed = 0;
  var returned = 0;
  
  var gen_time = gen_time_f();
  var proc_time = 0;
  var cur_proc_req = 0;
  
  var simulation_step_func;
  
  var proc_func = function() {
    if (cur_proc_req) {
      processed++;
      
      if (Math.random() < retprob) {
        returned++;
        queue[queue.length] = cur_proc_req - 1;
      }
      
      cur_proc_req = 0;
    }
    
    if (queue.length) {
      cur_proc_req = queue[0] + 1;
      queue.splice(0, 1);
      return proc_time_f();
    }
    
    return 0;
  };
  
  var gen_func = function() {
    if (!rcnt)
      return 0;
    
    rcnt--;
    
    if (!queue_add_req(queue, qlen))
      lost++;
    
    return gen_time_f();
  };
  
  var f = function() {
    update_sim_data(queue, rcnt, processed, lost, returned);
    
    if (!rcnt && !queue.length && !cur_proc_req)
      clearInterval(animation_interval_id);
    
    simulation_step_func();
  };
  
  sdata_a.innerHTML = qlen;
  if (mmode.selectedIndex) {
    var dt = Number(mdt.value);
    simulation_step_func = function() {
      if (gen_time > 0)
        gen_time -= dt;
      else
        gen_time = gen_func();
      
      if (proc_time > 0)
        proc_time -= dt;
      else
        proc_time = proc_func();
    }
  } else {
    simulation_step_func = function() {
      var gen_step = function() {
        proc_time -= Math.min(gen_time, proc_time);
        gen_time = gen_func();
      }
      
      var proc_step = function() {
        gen_time -= Math.min(gen_time, proc_time);
        proc_time = proc_func();
      }
      
      if (gen_time < proc_time) {
        gen_step();
        
        if (!gen_time)
          proc_step();
      } else {
        proc_step();
        
        if (!proc_time)
          gen_step();
      }
    }
  }
  
  update_sim_data(queue, rcnt, processed, lost, returned);
  animation_interval_id = setInterval(f, animation_interval);
  
  sim_button.innerHTML = "Остановить симуляцию";  
  sim_active = true;
}

function stop_simulation() {
  clearInterval(animation_interval_id);
  sim_button.innerHTML = "Запустить симуляцию";  
  sim_active = false;
}

function simulate() {
  if (sim_active)
    stop_simulation();
  else 
    start_simulation(get_time_generator, get_time_processor);
}

function get_result() {
  result.innerHTML = "";
}

document.addEventListener("DOMContentLoaded", init, false);