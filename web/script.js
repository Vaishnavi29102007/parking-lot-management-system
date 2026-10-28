const CAPACITY = 5;
let parked = [];
let waiting = [];
const $ = (id) => document.getElementById(id);

$("today").textContent = new Date().toLocaleDateString("en-IN", {
  day: "2-digit", month: "short", year: "numeric"
});

function timeLabel(date) {
  return date.toLocaleTimeString("en-IN", { hour: "2-digit", minute: "2-digit" });
}
function escapeHtml(value) {
  return String(value).replace(/[&<>"']/g, ch => ({
    "&": "&amp;", "<": "&lt;", ">": "&gt;", '"': "&quot;", "'": "&#39;"
  })[ch]);
}
function showToast(message) {
  const toast = $("toast");
  toast.textContent = message;
  toast.classList.add("show");
  clearTimeout(showToast.timer);
  showToast.timer = setTimeout(() => toast.classList.remove("show"), 2800);
}
function render() {
  $("availableCount").textContent = CAPACITY - parked.length;
  $("occupiedCount").textContent = parked.length;
  $("waitingCount").textContent = waiting.length;
  $("parkedBadge").textContent = `${parked.length} vehicle${parked.length === 1 ? "" : "s"}`;
  $("queueBadge").textContent = `${waiting.length} waiting`;

  $("parkingGrid").innerHTML = Array.from({ length: CAPACITY }, (_, i) => {
    const v = parked[i];
    return `<div class="slot ${v ? "occupied" : ""}">
      <span class="slot-number">SLOT ${String(i + 1).padStart(2, "0")}</span>
      <span class="car-icon">🚗</span>
      <span class="slot-status">${v ? "Occupied" : "Available"}</span>
      ${v ? `<span class="slot-vehicle">${escapeHtml(v.vehicle)}</span>` : ""}
    </div>`;
  }).join("");

  $("parkedTable").innerHTML = parked.map((v, i) => `<tr>
    <td>Slot ${String(i + 1).padStart(2, "0")}</td>
    <td>${escapeHtml(v.vehicle)}</td>
    <td>${escapeHtml(v.owner)}</td>
    <td>${v.time}</td>
    <td><button class="release-btn" data-release="${escapeHtml(v.vehicle)}">Release</button></td>
  </tr>`).join("");
  $("emptyParked").style.display = parked.length ? "none" : "flex";

  $("queueList").innerHTML = waiting.map((v, i) => `<li class="queue-item">
    <span class="queue-number">${i + 1}</span>
    <span class="queue-details"><strong>${escapeHtml(v.vehicle)}</strong><span>${escapeHtml(v.owner)} · Arrived ${v.time}</span></span>
    <span class="queue-position">#${i + 1} in line</span>
  </li>`).join("");
  $("emptyQueue").style.display = waiting.length ? "none" : "flex";
}
$("arrivalForm").addEventListener("submit", (event) => {
  event.preventDefault();
  const owner = $("owner").value.trim();
  const vehicle = $("vehicle").value.trim().toUpperCase();
  if (!owner || !vehicle) return;
  const allVehicles = [...parked, ...waiting];
  if (allVehicles.some(v => v.vehicle === vehicle)) {
    showToast("That vehicle number is already registered.");
    return;
  }
  const record = { owner, vehicle, time: timeLabel(new Date()) };
  if (parked.length < CAPACITY) {
    parked.push(record);
    showToast(`${vehicle} parked successfully.`);
  } else {
    waiting.push(record);
    showToast(`${vehicle} added to the waiting queue.`);
  }
  $("arrivalForm").reset();
  render();
});
$("parkedTable").addEventListener("click", (event) => {
  const button = event.target.closest("[data-release]");
  if (!button) return;
  const number = button.dataset.release;
  const index = parked.findIndex(v => v.vehicle === number);
  if (index < 0) return;
  parked.splice(index, 1);
  let message = `${number} has left the parking lot.`;
  if (waiting.length > 0) {
    const next = waiting.shift();
    parked.push(next);
    message += ` ${next.vehicle} from the queue is now parked.`;
  }
  render();
  showToast(message);
});
render();
