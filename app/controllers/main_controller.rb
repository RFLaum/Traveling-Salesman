class MainController < ApplicationController
  def landing; end

  def gene
    city_arr = []
    params[:coords].each do |num, pair|
      # city_arr << pair.map(&:to_i)
      city_arr << pair[0].to_i
      city_arr << pair[1].to_i
    end
    # logger.debug "gene test prefix #{city_arr}"
    require './cpp/cruncher'
    answer = Cruncher.new.solver(city_arr.dup);
    # logger.debug "gene test #{answer}"
    # logger.debug "seed: #{answer.pop}"
    # pool = GenePool.new(city_arr.dup, 500)
    # 50.times do
    #   pool.one_generation
    # end
    # until pool.num_genes >= 400 && pool.uniform?
    #   pool.one_generation
    # end
    # render json: { winner: pool.report_best }
    render json: { winner: answer }
  end
end
