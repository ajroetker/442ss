#include<stdio.h>
#include<set>
#include<queue>

int m, n;

int permute_cube_face(int face, int move){
  int left[6] = {3, 2, 6, 1, 5, 4};
  int down[6] = {5, 1, 3, 4, 6, 2};
  int up[6] = {2, 6, 3, 4, 1, 5};
  int right[6] = {4, 2, 1, 6, 5, 3};
  /* 1 = left
   * 2 = down
   * 3 = up
   * 4 = right
   *       _ _
   *      | 2 |
   *   _ _|_ _|_ _
   *  | 3 | 1 | 4 |
   *  |_ _|_ _|_ _|
   *      | 5 |
   *      |_ _|
   *      | 6 |
   *      |_ _|
   *
   */
  switch ( move ) {
    case 1:
      return left[face-1];
      break;
    case 2:
      return down[face-1];
      break;
    case 3:
      return up[face-1];
      break;
    case 4:
      return right[face-1];
      break;
    default:
      printf("That is not a valid move number: %d\n", move);
      return -1;
      break;
  }
}

int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

int* move_pos(int* board, int move){
  switch (move) {
    case 1:
      board[6] -= 1;
      return board;
      break;
    case 2:
      board[6] += n;
      return board;
      break;
    case 3:
      board[6] -= n;
      return board;
      break;
    case 4:
      board[6] += 1;
      return board;
      break;
  }
}

int* adjust_board(int* board, int move){
  int i = 0;
  int j;
  int is_cur_pos_marked =0;
  int seen_side_a = 0;
  board = move_pos(board, move);
  while(i < 6 && board[i] < 401){
    if (board[i] = board[6]) {
      is_cur_pos_marked = -1;
      j = i;
    }
  }
  while(i < 6){
    board[i] = permute_cube_face(board[i]-400, move) + 400;
    if (board[i] == 401){
      seen_side_a = -1;
      if (!is_cur_pos_marked) {
        board[i] = board[6];
      }
    }
  }
  if (!seen_side_a && !is_cur_pos_marked) {
    board[j] = 401;
  }
  qsort(board, 6, sizeof(int), compare);
  return board;
}

const bool is_bad_tile(std::set<int> bad_tiles, int tile){
  return bad_tiles.find(tile) != bad_tiles.end();
}
const bool is_in(std::set<int*> boards, int* board){
  return boards.find(board) != boards.end();
}

int are_we_done(int* board){
  int i = 0;
  while(i < 7){
   if(board[i] <= 400){
     return 0;
   }
  return -1;
  }
}


int find_the_goal(int* board, std::set<int> bad_tiles){
  std::set<int*> seen_boards;
  std::queue<int*> visit_me;
  int* next_board;
  int steps = 1;
  int* tmp_board;

  while(!visit_me.empty()){
    next_board = visit_me.front();
    seen_boards.insert(next_board);
    tmp_board = next_board;
    visit_me.pop();
    if (are_we_done(next_board)){
      return steps;
    }
    //Remember to add the board moves to each call
    //to adjust board
    steps += 1;
    if (next_board[6] <= n){
      if (next_board[6] == n) {
        tmp_board = adjust_board(next_board, 2);
        if(!is_in(seen_boards, tmp_board) && !is_bad_tile(bad_tiles, tmp_board[6])){
            visit_me.push(tmp_board);
            }
        tmp_board = adjust_board(next_board, 1);
        if(!is_in(seen_boards, tmp_board) && !is_bad_tile(bad_tiles, tmp_board[6])){
            visit_me.push(tmp_board);
            }
      }
      else if (next_board[6] == 1){
        tmp_board = adjust_board(next_board, 2);
        if(!is_in(seen_boards, tmp_board) && !is_bad_tile(bad_tiles, tmp_board[6])){
            visit_me.push(tmp_board);
            }
        tmp_board = adjust_board(next_board, 4);
        if(!is_in(seen_boards, tmp_board) && !is_bad_tile(bad_tiles, tmp_board[6])){
            visit_me.push(tmp_board);
            }
      }
      else {
        tmp_board = adjust_board(next_board, 2);
        if(!is_in(seen_boards, tmp_board) && !is_bad_tile(bad_tiles, tmp_board[6])){
            visit_me.push(tmp_board);
            }
        tmp_board = adjust_board(next_board, 4);
        if(!is_in(seen_boards, tmp_board) && !is_bad_tile(bad_tiles, tmp_board[6])){
            visit_me.push(tmp_board);
            }
        tmp_board = adjust_board(next_board, 1);
        if(!is_in(seen_boards, tmp_board) && !is_bad_tile(bad_tiles, tmp_board[6])){
            visit_me.push(tmp_board);
            }
      }
    }
    else if (next_board[6] > ((m-1)*n)) {
      if (next_board[6] == ((m-1)*n + 1)) {
        tmp_board = adjust_board(next_board, 3);
        if(!is_in(seen_boards, tmp_board) && !is_bad_tile(bad_tiles, tmp_board[6])){
            visit_me.push(tmp_board);
            }
        tmp_board = adjust_board(next_board, 4);
        if(!is_in(seen_boards, tmp_board) && !is_bad_tile(bad_tiles, tmp_board[6])){
            visit_me.push(tmp_board);
            }
      }
      else if (next_board[6] == (m*n)) {
        tmp_board = adjust_board(next_board, 3);
        if(!is_in(seen_boards, tmp_board) && !is_bad_tile(bad_tiles, tmp_board[6])){
            visit_me.push(tmp_board);
            }
        tmp_board = adjust_board(next_board, 1);
        if(!is_in(seen_boards, tmp_board) && !is_bad_tile(bad_tiles, tmp_board[6])){
            visit_me.push(tmp_board);
            }
      }
      else {
        tmp_board = adjust_board(next_board, 3);
        if(!is_in(seen_boards, tmp_board) && !is_bad_tile(bad_tiles, tmp_board[6])){
            visit_me.push(tmp_board);
            }
        tmp_board = adjust_board(next_board, 4);
        if(!is_in(seen_boards, tmp_board) && !is_bad_tile(bad_tiles, tmp_board[6])){
            visit_me.push(tmp_board);
            }
        tmp_board = adjust_board(next_board, 1);
        if(!is_in(seen_boards, tmp_board) && !is_bad_tile(bad_tiles, tmp_board[6])){
            visit_me.push(tmp_board);
            }
      }
    }
    else if (next_board[6] % n == 0) {
        tmp_board = adjust_board(next_board, 2);
        if(!is_in(seen_boards, tmp_board) && !is_bad_tile(bad_tiles, tmp_board[6])){
            visit_me.push(tmp_board);
            }
        tmp_board = adjust_board(next_board, 3);
        if(!is_in(seen_boards, tmp_board) && !is_bad_tile(bad_tiles, tmp_board[6])){
            visit_me.push(tmp_board);
            }
        tmp_board = adjust_board(next_board, 1);
        if(!is_in(seen_boards, tmp_board) && !is_bad_tile(bad_tiles, tmp_board[6])){
            visit_me.push(tmp_board);
            }
    }
    else if (next_board[6] % (1 + n) == 0) {
        tmp_board = adjust_board(next_board, 2);
        if(!is_in(seen_boards, tmp_board) && !is_bad_tile(bad_tiles, tmp_board[6])){
            visit_me.push(tmp_board);
            }
        tmp_board = adjust_board(next_board, 4);
        if(!is_in(seen_boards, tmp_board) && !is_bad_tile(bad_tiles, tmp_board[6])){
            visit_me.push(tmp_board);
            }
        tmp_board = adjust_board(next_board, 3);
        if(!is_in(seen_boards, tmp_board) && !is_bad_tile(bad_tiles, tmp_board[6])){
            visit_me.push(tmp_board);
            }
    }
    else {
        tmp_board = adjust_board(next_board, 1);
        if(!is_in(seen_boards, tmp_board) && !is_bad_tile(bad_tiles, tmp_board[6])){
            visit_me.push(tmp_board);
            }
        tmp_board = adjust_board(next_board, 2);
        if(!is_in(seen_boards, tmp_board) && !is_bad_tile(bad_tiles, tmp_board[6])){
            visit_me.push(tmp_board);
            }
        tmp_board = adjust_board(next_board, 4);
        if(!is_in(seen_boards, tmp_board) && !is_bad_tile(bad_tiles, tmp_board[6])){
            visit_me.push(tmp_board);
            }
        tmp_board = adjust_board(next_board, 3);
        if(!is_in(seen_boards, tmp_board) && !is_bad_tile(bad_tiles, tmp_board[6])){
            visit_me.push(tmp_board);
            }
    }
    return -1;
  }
}
int main(){

}
