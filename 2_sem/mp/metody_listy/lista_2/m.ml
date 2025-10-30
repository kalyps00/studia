let rec maxi xt =
  match xt with
  | [] -> neg_infinity
  | hd::tl ->
    let maximum = maxi tl in
    if  maximum <= hd then hd
    else maximum