class MainController < ApplicationController
  def landing; end

  def gene
    city_arr = []
    params[:coords].each do |num, pair|
      city_arr << pair.map(&:to_i)
    end
    pool = GenePool.new(city_arr.dup, 500)
    50.times do
      pool.one_generation
    end
    # until pool.num_genes >= 400 && pool.uniform?
    #   pool.one_generation
    # end
    render json: { winner: pool.report_best }
  end
end
