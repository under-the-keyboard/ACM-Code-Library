bool IsLeepYear(int y) {
  return (!(y % 4) && (y % 100)) || !(y % 400);
}